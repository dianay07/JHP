#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipComponent.generated.h"

class AEquipment;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JHP_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Equip)
	TSubclassOf<AEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = Equip)
	AEquipment* WeaponSlot;

	UPROPERTY(EditAnywhere, Category = Equip)
	TArray<AEquipment*> ArmorSlots;

public:	
	UEquipComponent();

	void RefreshEquipmentInfo();

protected:
	virtual void BeginPlay() override;

	TObjectPtr<ACharacter> OwnerCharacter;
};
