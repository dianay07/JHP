#include "StateComponent.h"

#include "JHP/JHPCharacter.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AJHPCharacter>(GetOwner());
}

void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStateComponent::SetInBattle(bool Input)
{
	InBattle = Input;
}

