#pragma once

#include "CoreMinimal.h"
#include "CharacterNotify.h"
#include "AnimNotify_Equip.generated.h"

UCLASS()
class JHP_API UAnimNotify_Equip : public UCharacterNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
