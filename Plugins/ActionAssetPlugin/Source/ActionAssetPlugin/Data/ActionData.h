#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActionAssetPlugin/Data/ActionDataStructure.h"
#include "ActionData.generated.h"

UCLASS()
class ACTIONASSETPLUGIN_API UActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FEquipAnimation DrawAnimation;									// 장착 애니메이션

	UPROPERTY(EditAnywhere)
	TArray<FAttackAnimation> AttackAnimations;											// 스킬 데이터

	UPROPERTY(EditAnywhere)
	TArray<FHitAnimation> HitAnimations;

public:
};
