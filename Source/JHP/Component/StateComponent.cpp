#include "StateComponent.h"

#include "JHP/Character/JHPCharacter.h"

UStateComponent::UStateComponent()
{
	
}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AJHPCharacter>(GetOwner());
	OwnerCharacter->OnEnterBattleCommand.AddUObject(this, &UStateComponent::SetInBattleTrue);
}

void UStateComponent::SetStateIdle()
{
	ChangeType(EStateType::Idle);
}

void UStateComponent::SetStateEvade()
{
	ChangeType(EStateType::Evade);
}

void UStateComponent::SetStateHitted()
{
	ChangeType(EStateType::Hitted);
}

void UStateComponent::SetStateDead()
{
	ChangeType(EStateType::Dead);
}

void UStateComponent::SetStateAction()
{
	ChangeType(EStateType::Action);
}

void UStateComponent::SetInBattleTrue()
{
	InBattle = true;
}

void UStateComponent::SetInBattleFalse()
{
	InBattle = false;
}

void UStateComponent::ChangeType(EStateType InType)
{
	if (this == nullptr) return;

	EStateType prevType = GetType();
	Type = InType;

	// DEBUG
	UEnum* StateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStateType"), true);
	UE_LOG(LogActor, Warning, TEXT("Onwer : %s, PrevState : %s, CurrentState : %s"), *GetOwner()->GetName(), *StateEnum->GetNameByIndex((int32)prevType).ToString(), *StateEnum->GetNameByIndex((int32)Type).ToString());

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Execute(prevType, InType);
}

