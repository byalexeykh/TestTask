// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "PrimitiveBase.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

AMyPlayerController::AMyPlayerController(){
	bShowMouseCursor = true;
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TraceCursor();
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
}

void AMyPlayerController::TraceCursor()
{
	FVector WorldLoc, WorldDir;
	FHitResult HitResult;

	DeprojectMousePositionToWorld(WorldLoc, WorldDir);

	FVector TraceStart = Cast<UCameraComponent>(GetPawn()->GetComponentByClass(UCameraComponent::StaticClass()))->GetComponentLocation();
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, GetPawn()->GetActorLocation() + (WorldDir * 50000), ECollisionChannel::ECC_Visibility);

	if (HitResult.GetActor()) {
		if (HitResult.GetActor()->IsA<APrimitiveBase>()) {
			OnPrimitiveHovered(Cast<APrimitiveBase>(HitResult.GetActor()));
		}
		else {
			OnPrimitiveLeave();
		}
	}
	else {
		OnPrimitiveLeave();
	}
}
