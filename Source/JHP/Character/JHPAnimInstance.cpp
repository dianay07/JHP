#include "JHPAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JHP/Character/JHPCharacter.h"
#include "JHP/Component/StateComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UJHPAnimInstance::NativeBeginPlay()
{
	OwnerCharacter = Cast<AJHPCharacter>(TryGetPawnOwner());

	if (OwnerCharacter != nullptr)
	{
		MovementComponent = Cast<UCharacterMovementComponent>(OwnerCharacter->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	}
}

void UJHPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(MovementComponent != nullptr)
	{
		Velocity = MovementComponent->Velocity;
		GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);

		IsFalling = MovementComponent->IsFalling();
		InBattle = OwnerCharacter->GetStateComponent()->InBattle;
	}

	if(InBattle == true)
	{
		const FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator();
		const FRotator rotator2 = OwnerCharacter->GetControlRotation();
		const FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2);
		PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, DeltaSeconds, 25);
		Direction = PrevRotation.Yaw;
	}
}
