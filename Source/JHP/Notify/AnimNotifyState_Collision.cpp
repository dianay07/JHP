#include "AnimNotifyState_Collision.h"

#include "JHP/Character/JHPCharacter.h"
#include "JHP/Component/EquipComponent.h"
#include "JHP/Equipment/Equipment.h"

FString UAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision NotifyState";
}

void UAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	Owner = Cast<AJHPCharacter>(MeshComp->GetOwner());

	if(Owner != nullptr)
	{
		// TODO : MeshComp->GetOwner가 안들어가 지는듯?

		UEquipComponent* EquipComponent = Cast<UEquipComponent>(Owner->GetComponentByClass(UEquipComponent::StaticClass()));
		EquipComponent->WeaponSlot->OnCollision();
	}
		
}

void UAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	if(Owner != nullptr)
	{
		UEquipComponent* EquipComponent = Cast<UEquipComponent>(Owner->GetComponentByClass(UEquipComponent::StaticClass()));

		if (EquipComponent != nullptr)
			EquipComponent->WeaponSlot->OffCollision();
	}
}