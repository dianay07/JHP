#pragma once

#include "CoreMinimal.h"
#include "CharacterNotify.h"
#include "AnimNotify_NextAction.generated.h"

UCLASS()
class JHP_API UAnimNotify_NextAction : public UCharacterNotify
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
