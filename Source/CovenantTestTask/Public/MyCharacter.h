// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class COVENANTTESTTASK_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();
private:
	// components
	class UCameraComponent* CameraComp;
};
