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
	FEquipAnimation DrawAnimation;									// ���� �ִϸ��̼�

	UPROPERTY(EditAnywhere)
	TArray<FAttackAnimation> AttackAnimations;											// ��ų ������

	UPROPERTY(EditAnywhere)
	TArray<FHitAnimation> HitAnimations;

public:
};
