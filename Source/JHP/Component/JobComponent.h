#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionAssetPlugin/Data/ActionDataStructure.h"
#include "JobComponent.generated.h"

class AJHPCharacter;
class UActionData;

// TODO : �� Ÿ�� �ٲ𶧸��� �����ؾ��� �̺�Ʈ�� ���� ��������Ʈ
DECLARE_MULTICAST_DELEGATE_TwoParams(FJobTypeChanged, EJob, EJob);


/* *���� �� �ش��ϴ� ������ ���� �� ��� ������Ʈ */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JHP_API UJobComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UActionData> DataAssets[static_cast<int32>(EJob::Max)];

public:
	void ChangeJob(EJob InType);

	void PlayEquipAnimation();
	void PlayUnEquipAnimation();
	void PlayAttackAnimation(int32 InIndex);
	void PlayHitAnimation(int32 InIndex);

public:
	UJobComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<AJHPCharacter> OwnerCharacter;

	EJob CurrentJob;
	FEquipAnimation EquipAnimation;
	TArray<FAttackAnimation> AttackAnimations;
	TArray<FHitAnimation> HitAnimations;
};

DECLARE_LOG_CATEGORY_EXTERN(LOG_JOBCOMPONENT, Log, Warning);
