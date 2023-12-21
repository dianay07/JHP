#include "CharacterNotify.h"

#include "JHP/Component/JobComponent.h"
#include "JHP/Component/EquipComponent.h"

DEFINE_LOG_CATEGORY(LOG_ANIMNOTIFY);

void UCharacterNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	AJHPCharacter* character = Cast<AJHPCharacter>(MeshComp->GetOwner());
	if (character == nullptr)
	{
		UE_LOG(LOG_ANIMNOTIFY, Log, TEXT("Notify : Charater is NULL"));
		return;
	}

	EquipComponent = Cast<UEquipComponent>(character->GetComponentByClass(UEquipComponent::StaticClass()));
	if(EquipComponent == nullptr)
	{
		UE_LOG(LOG_ANIMNOTIFY, Log, TEXT("Notify : EquipComponent is NULL"));
		return;
	}
}

