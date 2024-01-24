#include "JobComponent.h"

#include "JHP/Character/JHPCharacter.h"
#include "ActionAssetPlugin/Data/ActionData.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameFramework/Character.h"

// TODO :: ���� �ִϸ��̼� ��� ���� �ڵ带 �ۼ������� ? ��ġ, Ÿ�ӽ�ž ���� �ڵ带 ������ Montage ��� ���� Ŭ������ ���°� �ʿ�

void UJobComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AJHPCharacter>(GetOwner());

	OwnerCharacter->OnEnterBattleCommand.AddUObject(this, &UJobComponent::PlayEquipAnimation);
	OwnerCharacter->OnPlayAttackMontage.AddUObject(this, &UJobComponent::PlayAttackAnimation);

	OnWeaponBeginOverlap.AddUObject(this, &UJobComponent::OnAttachmentBeginOverlap);
}

/* �� ���� */
void UJobComponent::ChangeJob(EJob InType)
{
	// ������ ����
	// ���� �������� ����� �������� ���� �� ������ ���� üũ
	EJob prevType = CurrentJob;
	if (DataAssets[(int32)InType] == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("%s Job Asset isn't EXIST"), *UEnum::GetValueAsString(InType));

	// ���� ����� JobComponent�� ����� �����͵��� ��� ����
	CurrentJob = InType;
	EquipAnimation = DataAssets[(int32)InType]->DrawAnimation;
	AttackAnimations = DataAssets[(int32)InType]->AttackAnimations;
	HitAnimations = DataAssets[(int32)InType]->HitAnimations;

	// TODO : UI�� �ִٸ� ���ű��� (MultiCast Delegate�� �̺�Ʈ �����ϸ� �ɵ�)
}

// TODO : ����, Ż�� �ִϸ��̼� ���� ����, ���� üũ �ۼ��� ����
/* ���� ���� �ִϸ��̼� */
void UJobComponent::PlayEquipAnimation()
{
	// ���� ���� �ִϸ��̼� ���� üũ
	if (EquipAnimation.UnEquipMontage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("Equip Animation NOT EXIST"));

	// ���
	OwnerCharacter->PlayAnimMontage(EquipAnimation.DrawMontage, EquipAnimation.PlayRate);
}

/* ���� Ż�� �ִϸ��̼� */
void UJobComponent::PlayUnEquipAnimation()
{
	// ���� Ż�� �ִϸ��̼� ���� üũ
	if (EquipAnimation.UnEquipMontage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("UnEquip Animation NOT EXIST"));

	// ���
	OwnerCharacter->PlayAnimMontage(EquipAnimation.UnEquipMontage, EquipAnimation.PlayRate);
}

/* �Է� �ε����� ���� ���� �ִϸ��̼� ��� */
void UJobComponent::PlayAttackAnimation(int32 InIndex)
{
	// �ش� �ε��� ���� �ִϸ��̼� ���� üũ
	if (AttackAnimations[InIndex].Montage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("%d number Animation NOT EXIST"), InIndex);

	// ���
	OwnerCharacter->PlayAnimMontage(AttackAnimations[InIndex].Montage);
}

/* �Է� �ε����� ���� ��Ʈ �ִϸ��̼� ��� */
void UJobComponent::PlayHitAnimation(int32 InIndex)
{
	// �ش� �ε��� ���� �ִϸ��̼� ���� üũ
	if (HitAnimations[InIndex].Montage == nullptr)
		UE_LOG(LOG_JOBCOMPONENT, Fatal, TEXT("%d number Animation NOT EXIST"), InIndex);

	// ���
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

	// ������Ʈ ��������

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
