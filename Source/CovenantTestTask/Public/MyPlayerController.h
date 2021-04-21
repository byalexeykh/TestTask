// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class APrimitiveBase;

UCLASS()
class COVENANTTESTTASK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();
	
	UFUNCTION(BlueprintImplementableEvent)
		void OnPrimitiveHovered(APrimitiveBase* const &HoveredPrimitive);

	UFUNCTION(BlueprintImplementableEvent)
		void OnPrimitiveLeave();

protected:
	// overrides
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:
	// trace cursor in world space
	void TraceCursor();
};
