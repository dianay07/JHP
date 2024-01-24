#include "JobComponent.h"

#include "JHP/Character/JHPCharacter.h"
#include "ActionAssetPlugin/Data/ActionData.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameFramework/Character.h"

// TODO :: 당장 애니메이션 재생 관련 코드를 작성했지만 ? 런치, 타임스탑 관련 코드를 쓰려면 Montage 기능 관련 클래스를 빼는게 필요

void UJobComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AJHPCharacter>(GetOwner());

	OwnerCharacter->OnEnterBattleCommand.AddUObject(this, &UJobComponent::PlayEquipAnimation);
	OwnerCharacter->OnPlayAttackMontage.AddUObject(this, &UJobComponent::PlayAttackAnimation);

	OnWeaponBeginOverlap.AddUObject(this, &UJobComponent::OnAttachmentBeginOverlap);
}

/* 잡 변경 */
void UJobComponent::ChangeJob(EJob InType)
{
	// 직업을 변경
	// 이전 직업에서 변경될 직업으로 변경 시 데이터 에셋 체크
	EJob prevType = CurrentJob;
	if (DataAssets[(int32)InType] == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("%s Job Asset isn't EXIST"), *UEnum::GetValueAsString(InType));

	// 에셋 존재시 JobComponent에 저장될 데이터들을 모두 갱신
	CurrentJob = InType;
	EquipAnimation = DataAssets[(int32)InType]->DrawAnimation;
	AttackAnimations = DataAssets[(int32)InType]->AttackAnimations;
	HitAnimations = DataAssets[(int32)InType]->HitAnimations;

	// TODO : UI가 있다면 갱신까지 (MultiCast Delegate로 이벤트 연결하면 될듯)
}

// TODO : 장착, 탈착 애니메이션 전투 시작, 종료 체크 작성후 변경
/* 무기 장착 애니메이션 */
void UJobComponent::PlayEquipAnimation()
{
	// 무기 장착 애니메이션 유무 체크
	if (EquipAnimation.UnEquipMontage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("Equip Animation NOT EXIST"));

	// 재생
	OwnerCharacter->PlayAnimMontage(EquipAnimation.DrawMontage, EquipAnimation.PlayRate);
}

/* 무기 탈착 애니메이션 */
void UJobComponent::PlayUnEquipAnimation()
{
	// 무기 탈착 애니메이션 유무 체크
	if (EquipAnimation.UnEquipMontage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("UnEquip Animation NOT EXIST"));

	// 재생
	OwnerCharacter->PlayAnimMontage(EquipAnimation.UnEquipMontage, EquipAnimation.PlayRate);
}

/* 입력 인덱스에 따른 공격 애니메이션 재생 */
void UJobComponent::PlayAttackAnimation(int32 InIndex)
{
	// 해당 인덱스 공격 애니메이션 유무 체크
	if (AttackAnimations[InIndex].Montage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("%d number Animation NOT EXIST"), InIndex);

	// 재생
	OwnerCharacter->PlayAnimMontage(AttackAnimations[InIndex].Montage);
}

/* 입력 인덱스에 따른 히트 애니메이션 재생 */
void UJobComponent::PlayHitAnimation(int32 InIndex)
{
	// 해당 인덱스 공격 애니메이션 유무 체크
	if (HitAnimations[InIndex].Montage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("%d number Animation NOT EXIST"), InIndex);

	// 재생
	OwnerCharacter->PlayAnimMontage(AttackAnimations[InIndex].Montage);
}

void UJobComponent::DoAction()
{
	if (AttackAnimations.Num() < 1) return;

	if (bEnable == true)
	{
		bEnable = false;
		bExist = true;

		return;
	}

	// 스테이트 공격으로

	PlayAttackAnimation(AttackAnimationIndex);
}

void UJobComponent::BeginDoAction()
{
	if (bExist == false)
		return;

	bExist = false;
	OwnerCharacter->StopAnimMontage();
	PlayAttackAnimation(++AttackAnimationIndex);
}

void UJobComponent::BeginAction(UAnimMontage* InMontage)
{
	if (InMontage->GetName().Contains("Frank_RPG_Warrior_Combo") == false) return;

	if (OwnerCharacter->GetStateComponent()->IsActionMode() == false)
		OwnerCharacter->GetStateComponent()->SetStateAction();

	UE_LOG(LogTemp, Error, TEXT("%s Enter Action Mode"), *OwnerCharacter->GetName());
}

void UJobComponent::EndAction(UAnimMontage* InMontage, bool Interupt)
{
	if (InMontage->GetName().Contains("Frank_RPG_Warrior_Combo") == false) return;

	OwnerCharacter->GetStateComponent()->SetStateIdle();

	bEnable = false;

	if (AttackAnimationIndex > 0)
		AttackAnimationIndex = 0;

	UE_LOG(LogTemp, Error, TEXT("%s Enter Idle Mode"), *OwnerCharacter->GetName());
}

void UJobComponent::SetAttackAnimationIndex(int value)
{
	AttackAnimationIndex = value;
}

UJobComponent::UJobComponent()
{
	CurrentJob = EJob::Max;
}

void UJobComponent::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	if(InOther == nullptr) return;

	FSkillDamageEvent e;
	e.HitData = &HitAnimations[0];

	InOther->TakeDamage(0, e, InAttacker->GetController(), InAttackCuaser);

	for (ACharacter* hitted : Hitted)
		if(hitted == InOther) return;

	Hitted.AddUnique(InOther);
	UE_LOG(LogTemp, Error, TEXT(""));

	PlayHitAnimation(0);
}

DEFINE_LOG_CATEGORY(LOG_JOBCOMPONENT);
