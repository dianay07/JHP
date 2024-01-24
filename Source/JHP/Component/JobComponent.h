#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionAssetPlugin/Data/ActionDataStructure.h"
#include "JobComponent.generated.h"

class AJHPCharacter;
class UActionData;

// TODO : 잡 타입 바뀔때마다 연결해야할 이벤트들 받을 딜리게이트
DECLARE_MULTICAST_DELEGATE_TwoParams(FJobTypeChanged, EJob, EJob);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FWeaponBeginOverlap, ACharacter*, AActor*, ACharacter*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FWeaponEndOverlap, ACharacter*, ACharacter*);

/* *직업 별 해당하는 데이터 관리 및 사용 컴포넌트 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JHP_API UJobComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UActionData> DataAssets[static_cast<int32>(EJob::Max)];

public:
	void ChangeJob(EJob InType);

private:
	void PlayEquipAnimation();
	void PlayUnEquipAnimation();
	void PlayAttackAnimation(int32 InIndex);
	void PlayHitAnimation(int32 InIndex);

public:
	void DoAction();
	void BeginDoAction();

	UFUNCTION()
	void BeginAction(UAnimMontage* InMontage);

	UFUNCTION()
	void EndAction(UAnimMontage* InMontage, bool Interupt);

	FORCEINLINE int GetAttackAnimationIndex() { return AttackAnimationIndex; }
	void SetAttackAnimationIndex(int value);

	FORCEINLINE bool GetCanCombo() { return bEnable; }

	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	UJobComponent();

public:
	FWeaponBeginOverlap OnWeaponBeginOverlap;
	FWeaponEndOverlap OnWeaponEndOverlap;
		
protected:
	void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther);

private:
	TObjectPtr<AJHPCharacter> OwnerCharacter;

	EJob CurrentJob;
	FEquipAnimation EquipAnimation;
	TArray<FAttackAnimation> AttackAnimations;
	TArray<FHitAnimation> HitAnimations;

	int AttackAnimationIndex = 0;
	bool bEnable = false;
	bool bExist = false;

	TArray<ACharacter*> Hitted;
};

DECLARE_LOG_CATEGORY_EXTERN(LOG_JOBCOMPONENT, Log, Warning);
