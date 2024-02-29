// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "JHP/Component/StateComponent.h"
#include "JHPCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStateComponent;
class UJobComponent;
class UEquipComponent;

DECLARE_MULTICAST_DELEGATE(FOnEnterBattleCommandDelegate);	// 전투 상태 변경
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayAttackMontage, int32);

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
	TObjectPtr<UJobComponent> Job;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipComponent> EquipComponent;

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return CameraComponent; }
	FORCEINLINE UStateComponent* GetStateComponent() const { return StateComponent; }
	FORCEINLINE UJobComponent* GetJobComponent() const { return Job; }
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GuardAction;

public:
	AJHPCharacter();

	void ControlCamera(bool Input);

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();
	void StartGuard();
	void StopGuard();

protected:
	// State 관련
	void StateTypeChanged(EStateType PrevType, EStateType InType);

public:
	// 장착 관련
	FOnEnterBattleCommandDelegate OnEnterBattleCommand;
	// 공격 관련
	FOnPlayAttackMontage OnPlayAttackMontage;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
};