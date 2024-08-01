// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CCharacterBase.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
//#include "JHP/Component/StateComponent.h"
#include "MotionWarpingComponent.h"
#include "JHP/Component/StatusComponent.h"
#include "JHPCharacter.generated.h"

class UCWB_HUD;
class USpringArmComponent;
class UCameraComponent;
class UStateComponent;
class UJobComponent;
class UEquipComponent;
class UTargetingComponent;

class UCUIManager;

DECLARE_MULTICAST_DELEGATE(FOnEnterBattleCommandDelegate);	// 전투 상태 변경
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayAttackMontage, int32);

UCLASS(config=Game)
class AJHPCharacter : public ACCharacterBase
{
	GENERATED_BODY()

	/* Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UJobComponent> JobComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipComponent> EquipComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTargetingComponent> TargetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

public:
	/* Getter */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return CameraComponent; }
	FORCEINLINE UStatusComponent* GetStatusComponent() const { return StatusComponent; }
	FORCEINLINE UJobComponent* GetJobComponent() const { return JobComponent; }
	FORCEINLINE UTargetingComponent* GetTargetComponent() const { return TargetComponent; }
	FORCEINLINE UAnimInstance* GetAnimInstance() const { return GetMesh()->GetAnimInstance(); }
	FORCEINLINE UCWB_HUD* GetHUD() const { return WB_HUD; }


	/* Input */
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
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* VaultAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GuardAction;

	/* UI */
private:
	TSubclassOf<UCWB_HUD> UCWB_HUD_Class;
	TObjectPtr<UCWB_HUD> WB_HUD = nullptr;

public:
	AJHPCharacter();

	void ControlCamera(bool Input);

	// Input
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();
	void StartGuard();
	void StopGuard();

	// Sprint
	FTimerHandle TimerHandle;
	void Sprint();
	void StopSprint();
	UFUNCTION()
	void DrainStamina();


	// 파쿠르 ( Vault )
public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* VaultMontage;

	void Vault();
	void VaultMotionWarp();

private:	
	FVector VaultStartPos;
	FVector VaultMiddlePos;
	FVector VaultLandPos;

	bool CanWarp;

	// Damage
public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void AnyDamage(float InValue);
	void Die();

protected:
	// State 관련
	void StateTypeChanged(EStateType PrevType, EStateType InType) override;

public:
	// 장착 관련
	FOnEnterBattleCommandDelegate OnEnterBattleCommand;
	// 공격 관련
	FOnPlayAttackMontage OnPlayAttackMontage;

	UFUNCTION()
	void SetMovementMode();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

private:
	//TObjectPtr<UCUIManager> UIManager = nullptr;
};