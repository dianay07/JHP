#include "AnimNotify_NextAction.h"

#include "JHP/Component/JobComponent.h"

FString UAnimNotify_NextAction::GetNotifyName_Implementation() const
{
	return "NextAction";
}

void UAnimNotify_NextAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	Character = Cast<AJHPCharacter>(MeshComp->GetOwner());
	if (Character == nullptr) return;

	if(JobComponent != nullptr)
	{
		JobComponent->BeginDoAction();
	}
}
