#include "AnimNotify_Equip.h"

#include "JHP/Component/EquipComponent.h"

FString UAnimNotify_Equip::GetNotifyName_Implementation() const
{
	return "Notify_Equip";
}

void UAnimNotify_Equip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(EquipComponent != nullptr)
		EquipComponent->EquipWeapon();
}
