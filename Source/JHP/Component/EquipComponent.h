#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipComponent.generated.h"

class AJHPCharacter;
class AEquipment;

/* *캐릭터에 붙어 Equipmnet 타입의 아이템들을 관리 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JHP_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Equip)
	TSubclassOf<AEquipment> WeaponEquipmentClass;

	UPROPERTY(EditAnywhere, Category = Equip)
	AEquipment* WeaponSlot;

	FORCEINLINE AEquipment* GetWeaponEquipment() { return WeaponSlot; }

	UPROPERTY(EditAnywhere, Category = Equip)
	TArray<AEquipment*> ArmorSlots;

public:	
	UEquipComponent();

	void RefreshEquipmentInfo();

	void EquipWeapon();
	void UnEquipWeapon();

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<AJHPCharacter> OwnerCharacter;
};
