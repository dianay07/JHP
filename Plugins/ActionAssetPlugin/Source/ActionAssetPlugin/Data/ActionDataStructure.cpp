#include "ActionDataStructure.h"
#include "ActionUtility.h"

void FAttackAnimation::PlayAction(ACharacter* InOwner)
{
	if (Montage == nullptr)
		return;

	InOwner->PlayAnimMontage(Montage, PlayRate);
}

void FAttackAnimation::PlayEffect(UWorld* InWorld, const FVector& InLocation)
{
	if (Effect == nullptr)
		return;

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);
	transform.AddToTranslation(InLocation);

	ActionUtility::PlayEffect(InWorld, Effect, transform);
}

void FAttackAnimation::PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation)
{
	if (Effect == nullptr)
		return;

	FTransform transform;
	transform.SetLocation(InLocation + InRotation.RotateVector(EffectLocation));
	transform.SetScale3D(EffectScale);

	ActionUtility::PlayEffect(InWorld, Effect, transform);
}

///////////////////////////////////////////////////////////////////////////////

void FHitAnimation::PlayEffect(UWorld* InWorld, const FVector& InLocation)
{
	if (Effect == nullptr)
		return;

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);
	transform.AddToTranslation(InLocation);

	ActionUtility::PlayEffect(InWorld, Effect, transform);
}

void FHitAnimation::PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation)
{
	if (Effect == nullptr)
		return;

	FTransform transform;
	transform.SetLocation(InLocation + InRotation.RotateVector(EffectLocation));
	transform.SetScale3D(EffectScale);

	ActionUtility::PlayEffect(InWorld, Effect, transform);
}
