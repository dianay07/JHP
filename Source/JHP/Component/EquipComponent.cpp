#include "EquipComponent.h"

#include "GameFramework/Character.h"
#include "JHP/Character/JHPCharacter.h"
#include "JHP/Equipment/Equipment.h"

UEquipComponent::UEquipComponent()
{
	EquipmentClass = AEquipment::StaticClass();
}

void UEquipComponent::RefreshEquipmentInfo()
{
}

void UEquipComponent::Equip()
{
	// TODO : 개선 필요 부분
	WeaponSlot->AttachTo("handr_weapon");
}

void UEquipComponent::UnEquip()
{
	WeaponSlot->AttachTo("Holster_Weapon");
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

		WeaponSlot = OwnerCharacter->GetWorld()->SpawnActor<AEquipment>(EquipmentClass, params);
		WeaponSlot->AttachTo("Holster_Weapon");
	}
	
}
