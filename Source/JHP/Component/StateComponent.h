#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

class AJHPCharacter;

UENUM()
enum class EStateType : uint8
{
	Idle = 0, Evade, Hitted, Guard, Dead, Action, Max,
};

DECLARE_DELEGATE_TwoParams(FStateTypeChanged, EStateType, EStateType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JHP_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsEvadeMode() { return Type == EStateType::Evade; }
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	FORCEINLINE bool IsGuardMode() { return Type == EStateType::Guard; }

	EStateType GetType() { return Type; }

	FORCEINLINE bool IsInBattle() { return InBattle; }

public:
	UPROPERTY(BlueprintReadOnly)
	bool InBattle;

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetStateIdle();
	void SetStateEvade();
	void SetStateHitted();
	void SetStateDead();
	void SetStateAction();
	void SetStateGuard();

	void SetInBattleTrue();
	void SetInBattleFalse();

private:
	UFUNCTION()
	void ChangeType(EStateType InType);

public:
	FStateTypeChanged OnStateTypeChanged;

private:
	TObjectPtr<ACharacter> OwnerCharacter;

	EStateType Type;
};
