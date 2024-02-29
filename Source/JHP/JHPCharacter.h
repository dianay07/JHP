// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "JHPCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStateComponent;
class UJobComponent;

UCLASS(config=Game)
class AJHPCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStateComponent> StateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UJobComponent> JobComponent;

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return CameraComponent; }
	FORCEINLINE UStateComponent* GetStateComponent() const { return StateComponent; }
	FORCEINLINE UJobComponent* GetJobComponent() const { return JobComponent; }
	FORCEINLINE UAnimInstance* GetAnimInstance() const { return GetMesh()->GetAnimInstance(); }

	/* Input */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

public:
	AJHPCharacter();

	void ControlCamera(bool Input);

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
};