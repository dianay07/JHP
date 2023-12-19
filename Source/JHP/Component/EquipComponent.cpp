#include "EquipComponent.h"

#include "GameFramework/Character.h"
#include "JHP/Equipment/Equipment.h"

UEquipComponent::UEquipComponent()
{
	EquipmentClass = AEquipment::StaticClass();
}

void UEquipComponent::RefreshEquipmentInfo()
{
}

void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if(WeaponSlot == nullptr)
	{
		FActorSpawnParameters params;
		params.Owner = OwnerCharacter;

		WeaponSlot = OwnerCharacter->GetWorld()->SpawnActor<AEquipment>(EquipmentClass, params);
		WeaponSlot->AttachTo("HandR_Weapon");
	}
}
