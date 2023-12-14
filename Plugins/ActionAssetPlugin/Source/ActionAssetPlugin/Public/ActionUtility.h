#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystem.h"

class ACTIONASSETPLUGIN_API ActionUtility
{
public:
	static void PlayEffect(UWorld* InWorld, UFXSystemAsset* InAsset, const FTransform& InTransform, USkeletalMeshComponent* InMesh = nullptr, FName InSocketName = NAME_None)
	{
		UParticleSystem* particle = Cast<UParticleSystem>(InAsset);
		UNiagaraSystem* niagara = Cast<UNiagaraSystem>(InAsset);

		const FVector location = InTransform.GetLocation();
		const FRotator rotation = static_cast<FRotator>(InTransform.GetRotation());
		const FVector scale = InTransform.GetScale3D();
		//FVector scale = InScale;

		if (InMesh != nullptr)
		{
			if (particle != nullptr)
			{
				UGameplayStatics::SpawnEmitterAttached(particle, InMesh, InSocketName, location, rotation, scale);
				return;
			}

			if (niagara != nullptr)
			{
				UNiagaraFunctionLibrary::SpawnSystemAttached(niagara, InMesh, InSocketName, location, rotation, scale, EAttachLocation::KeepRelativeOffset, true, ENCPoolMethod::None);
				return;
			}
		}

		if (particle != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(InWorld, particle, InTransform);
			return;
		}

		if (niagara != nullptr)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(InWorld, niagara, location, rotation, scale);
			return;
		}
	}

	static ACharacter* GetNearlyFrontAngle(const ACharacter* InCharacter, TArray<ACharacter*> InArray)
	{
		float Angle = 0.0f;
		ACharacter* Candidate = nullptr;

		for (ACharacter* character : InArray)
		{
			if (character != nullptr)
			{
				const FVector direct = (character->GetActorLocation() - InCharacter->GetActorLocation()).GetSafeNormal2D();
				const FVector forward = InCharacter->GetActorForwardVector();

				if (UKismetMathLibrary::Dot_VectorVector(direct, forward) >= Angle)
				{
					Angle = UKismetMathLibrary::Dot_VectorVector(direct, forward);
					Candidate = character;
				}
			}
		}

		return Candidate;
	}
};
