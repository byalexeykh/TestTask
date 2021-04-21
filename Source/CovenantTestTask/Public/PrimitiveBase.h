// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrimitiveBase.generated.h"

class UMaterialInstanceDynamic;

UENUM(BlueprintType)
namespace EPrimitive {
	enum Type {
		Cube,
		Sphere,
		Cone
	};
}

namespace EPrimitive {
	inline FString ToString(EPrimitive::Type T) {
		return FindObject<UEnum>(ANY_PACKAGE, TEXT("EPrimitive"))->GetDisplayNameTextByIndex(T).ToString();
	}
}

USTRUCT(Blueprintable)
struct FPrimitiveCharacteristics {

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		FLinearColor Color;
	
	UPROPERTY(BlueprintReadWrite)
		FVector Size;

	UPROPERTY(BlueprintReadWrite)
		FString PrimitiveType;
};

UCLASS()
class COVENANTTESTTASK_API APrimitiveBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APrimitiveBase();

	void SetParams(FLinearColor _Color, FVector _Size);

	// Gameplay 
	UFUNCTION(BlueprintCallable)
	FPrimitiveCharacteristics GetPrimitiveCharacteristics();

	static UClass* GetRandomPrimitiveStaticClass();

protected:
	// components
	UStaticMeshComponent* StaticMeshComp;

	// Primitives characteristics
	EPrimitive::Type PrimitiveType = EPrimitive::Cube;
	FLinearColor Color = FLinearColor::Blue;
	FVector Size = FVector::OneVector;

	// Mesh reference
	UStaticMesh* Mesh;

private:
	// Dynamic material for dynamic color changing
	UMaterialInstanceDynamic* DynamicMat;
	
	// Array with all childs of APrimitiveBase class
	static TArray<UClass*> AllPrimitives;
};
