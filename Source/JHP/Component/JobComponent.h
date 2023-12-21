#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionAssetPlugin/Data/ActionDataStructure.h"
#include "JobComponent.generated.h"

class AJHPCharacter;
class UActionData;

// TODO : 잡 타입 바뀔때마다 연결해야할 이벤트들 받을 딜리게이트
DECLARE_MULTICAST_DELEGATE_TwoParams(FJobTypeChanged, EJob, EJob);


/* *직업 별 해당하는 데이터 관리 및 사용 컴포넌트 */
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
