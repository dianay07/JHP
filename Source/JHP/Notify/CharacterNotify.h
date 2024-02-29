#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "JHP/Character/JHPCharacter.h"
#include "CharacterNotify.generated.h"

/* Character Notify BaseClass */

DECLARE_LOG_CATEGORY_EXTERN(LOG_ANIMNOTIFY, Log, Warning);

UCLASS()
class JHP_API UCharacterNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	TObjectPtr<AJHPCharacter> Character;
	TObjectPtr<UJobComponent> JobComponent;
	TObjectPtr<UEquipComponent> EquipComponent;
};