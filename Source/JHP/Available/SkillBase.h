#pragma once

#include "CoreMinimal.h"
#include "ActionAssetPlugin/Data/ActionData.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

UCLASS()
class JHP_API USkillBase : public UObject
{
	GENERATED_BODY()

public:
	USkillBase(const FObjectInitializer& ObjectInitializer);

	void BeginPlay(ACharacter* InOwner, UActionData* InData);


private:
	FEquipAnimation DrawAnimation;
	TArray<FAttackAnimation> AttackAnimations;
	TArray<FHitAnimation> HitAnimations;
};
