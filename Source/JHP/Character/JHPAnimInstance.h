#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JHPAnimInstance.generated.h"

class AJHPCharacter;
class UCharacterMovementComponent;

UCLASS()
class JHP_API UJHPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly)
	float Direction;

	UPROPERTY(BlueprintReadOnly)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly)
	bool InBattle;

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	TObjectPtr<AJHPCharacter> OwnerCharacter;
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	FRotator PrevRotation;
};
