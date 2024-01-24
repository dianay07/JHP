#include "AnimNotifyState_Combo.h"

#include "JHP/Character/JHPCharacter.h"
#include "JHP/Component/JobComponent.h"

FString UAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combos NotifyState";
}

void UAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	Owner = Cast<AJHPCharacter>(MeshComp->GetOwner());
	if (Owner == nullptr) return;

	UJobComponent* JobComponent = Cast<UJobComponent>(Owner->GetComponentByClass(UJobComponent::StaticClass()));
	if (JobComponent != nullptr)
	{
		JobComponent->EnableCombo();
	}
}

void UAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	Owner = Cast<AJHPCharacter>(MeshComp->GetOwner());
	if (Owner == nullptr) return;

	UJobComponent* JobComponent = Cast<UJobComponent>(Owner->GetComponentByClass(UJobComponent::StaticClass()));
	if (JobComponent != nullptr)
	{
		JobComponent->DisableCombo();
	}
}