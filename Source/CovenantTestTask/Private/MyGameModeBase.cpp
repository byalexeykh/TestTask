// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "EngineUtils.h"
#include "Landscape.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "DrawDebugHelpers.h"
#include "PrimitiveBase.h"

#define LandscapeOnly_Channel ECollisionChannel::ECC_GameTraceChannel1

AMyGameModeBase::AMyGameModeBase() {
	PlayerControllerClass = ConstructorHelpers::FObjectFinder<UClass>(TEXT("/Game/Blueprints/MyPlayerController_BP.MyPlayerController_BP_C")).Object;
	DefaultPawnClass = AMyCharacter::StaticClass();
}

void AMyGameModeBase::BeginPlay() {
	Super::BeginPlay();
	RandomSpawn();
}

void AMyGameModeBase::RandomSpawn() {
	ALandscape* Land = nullptr;

	for (TActorIterator<ALandscape> _Land(GetWorld()); _Land; ++_Land) {
		Land = *_Land;
	}

	if (Land) {
		
		// Num of objects to spawn
		int32 ObjectsNum = 400;
		
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex = true;
		
		FVector temp, LandBoundsExtent;
		FVector PosToSpawnPlanar, PosToSpawn;
		
		FRotator SpawnedObjectRot;

		for (int32 i = 0; i < ObjectsNum; i++) {
			Land->GetActorBounds(false, temp, LandBoundsExtent);

			PosToSpawnPlanar = FVector(
				FMath::RandRange(Land->GetActorLocation().X, LandBoundsExtent.X),
				FMath::RandRange(Land->GetActorLocation().Y, LandBoundsExtent.Y),
				Land->GetActorLocation().Z - 20
			);

			// projecting planar spawn locations on landscape
			GetWorld()->LineTraceSingleByChannel(
				HitResult,
				PosToSpawnPlanar,
				PosToSpawnPlanar + FVector(0, 0, LandBoundsExtent.Z * 1000),
				LandscapeOnly_Channel,
				QueryParams
			);

			if (HitResult.GetActor()) {
				if (HitResult.GetActor()->IsA<ALandscape>()) {
					PosToSpawn = HitResult.Location;
					SpawnedObjectRot = FRotationMatrix::MakeFromZ(HitResult.Normal * -1).Rotator();

					// Primitive spawn
					APrimitiveBase* Primitive = GetWorld()->SpawnActorDeferred<APrimitiveBase>(
						APrimitiveBase::GetRandomPrimitiveStaticClass(),
						FTransform::Identity,
						nullptr,
						nullptr,
						ESpawnActorCollisionHandlingMethod::AlwaysSpawn
						);
					// creating params
					FVector Size = FVector(FMath::RandRange(0.6f, 1.f));
					// assigning params
					Primitive->SetParams(SelectRandomColorFromRGB(), Size);
					Primitive->FinishSpawning(FTransform(SpawnedObjectRot.Quaternion(), PosToSpawn, Size));
				}
			}
		}
	}
}

FLinearColor AMyGameModeBase::SelectRandomColorFromRGB()
{
	switch (FMath::RandRange(0, 2))
	{
	case 0:
		return FLinearColor::Red;
		break;
	case 1:
		return FLinearColor::Green;
		break;
	case 2:
		return FLinearColor::Blue;
		break;
	default:
		return FLinearColor();
		break;
	}
}
