#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_Collision.generated.h"

UCLASS()
class JHP_API UAnimNotifyState_Collision : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	TObjectPtr<class AJHPCharacter> Owner;
};
