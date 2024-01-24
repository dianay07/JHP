#include "EquipComponent.h"

#include "JobComponent.h"
#include "GameFramework/Character.h"
#include "JHP/Character/JHPCharacter.h"
#include "JHP/Equipment/Equipment.h"

UEquipComponent::UEquipComponent()
{
	WeaponEquipmentClass = AEquipment::StaticClass();
}

void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AJHPCharacter>(GetOwner());
	//OwnerCharacter->OnEnterBattleCommand.AddUObject(this, &UEquipComponent::Equip);

	if (WeaponSlot == nullptr)
	{
		FActorSpawnParameters params;
		params.Owner = Cast<ACharacter>(OwnerCharacter);

		WeaponSlot = OwnerCharacter->GetWorld()->SpawnActor<AEquipment>(WeaponEquipmentClass, params);

		// TODO : 이건 노티파이로 가야할듯 ?
		/*if(OwnerCharacter->GetAnimInstance() != nullptr)
		{
			OwnerCharacter->GetAnimInstance()->OnMontageStarted.AddDynamic(WeaponSlot, &AEquipment::OnCollision);
			OwnerCharacter->GetAnimInstance()->OnMontageEnded.AddDynamic(WeaponSlot, &AEquipment::OffCollision);
		}*/

		// ActionMode <-> IdleMode
		if(OwnerCharacter->GetAnimInstance() != nullptr)
		{
			OwnerCharacter->GetAnimInstance()->OnMontageStarted.AddDynamic(OwnerCharacter->GetJobComponent(), &UJobComponent::BeginAction);
			OwnerCharacter->GetAnimInstance()->OnMontageEnded.AddDynamic(OwnerCharacter->GetJobComponent(), &UJobComponent::EndAction);
		}
	}

	WeaponSlot->AttachTo(OwnerCharacter->GetMesh(), "Holster_Weapon");
}

void UEquipComponent::RefreshEquipmentInfo()
{
}

void UEquipComponent::EquipWeapon()
{
	// TODO : 개선 필요 부분
	WeaponSlot->AttachTo(OwnerCharacter->GetMesh(), "handr_weapon");
}

void UEquipComponent::UnEquipWeapon()
{
	WeaponSlot->AttachTo(OwnerCharacter->GetMesh(), "Holster_Weapon");
}
