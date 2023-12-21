#include "JobComponent.h"
#include "JobComponent.h"

#include "JHP/Character/JHPCharacter.h"
#include "ActionAssetPlugin/Data/ActionData.h"
#include "GameFramework/Character.h"

// TODO :: ���� �ִϸ��̼� ��� ���� �ڵ带 �ۼ������� ? ��ġ, Ÿ�ӽ�ž ���� �ڵ带 ������ Montage ��� ���� Ŭ������ ���°� �ʿ�

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
	if(AttackAnimations[InIndex].Montage == nullptr)
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

UJobComponent::UJobComponent()
{
	CurrentJob = EJob::Max;
}

void UJobComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AJHPCharacter>(GetOwner());
	// Notify�� ����
	OwnerCharacter->OnEnterBattleCommand.AddUObject(this, &UJobComponent::PlayEquipAnimation);
	OwnerCharacter->OnPlayAttackMontage.AddUObject(this, &UJobComponent::PlayAttackAnimation);
}

void UJobComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

DEFINE_LOG_CATEGORY(LOG_JOBCOMPONENT);