// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimitiveBase.h"

// Static array
TArray<UClass*> APrimitiveBase::AllPrimitives;

// Sets default values
APrimitiveBase::APrimitiveBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Components init
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");

	// Mesh default reference
	Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Primitive/Shapes/Shape_Cube.Shape_Cube")).Object;

	// Default mesh
	StaticMeshComp->SetStaticMesh(Mesh);

	// Creating new dynamic material
	DynamicMat = UMaterialInstanceDynamic::Create(StaticMeshComp->GetStaticMesh()->GetMaterial(0), NULL);
	StaticMeshComp->SetMaterial(0, DynamicMat);

	RootComponent = StaticMeshComp;
	
	// Checking if this is a base
	if (GetClass() == APrimitiveBase::StaticClass()) {
		// Filling array with all childrens
		AllPrimitives.Empty();
		for (TObjectIterator<UClass> Primitive; Primitive; ++Primitive) {
			if (Primitive->IsChildOf(APrimitiveBase::StaticClass()) && *Primitive != APrimitiveBase::StaticClass()) {
				AllPrimitives.Add(*Primitive);
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Found %i primitives"), AllPrimitives.Num());
	}
}

void APrimitiveBase::SetParams(FLinearColor _Color, FVector _Size)
{
	Color = _Color;
	Size = _Size;

	// Setting size
	StaticMeshComp->SetWorldScale3D(Size);

	// Setting color
	DynamicMat->SetVectorParameterValue("Color", Color);

}

FPrimitiveCharacteristics APrimitiveBase::GetPrimitiveCharacteristics()
{
	FPrimitiveCharacteristics PC;
	PC.Color = Color;
	PC.Size = Size;
	PC.PrimitiveType = EPrimitive::ToString(PrimitiveType);
	return PC;
}

UClass* APrimitiveBase::GetRandomPrimitiveStaticClass()
{
	return AllPrimitives[FMath::RandRange(0, AllPrimitives.Num() - 1)];
}
