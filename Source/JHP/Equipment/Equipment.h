#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

DECLARE_MULTICAST_DELEGATE(FEquipmentBeginCollision);
DECLARE_MULTICAST_DELEGATE(FEquipmentEndCollision);



UCLASS()
class JHP_API AEquipment : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMeshComponent* EquipmentSM;

public:
	// UFUNCTION Á¦°Å ??
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void AttachTo(USkeletalMeshComponent* Mesh,FName InSocketName);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void AttachToCollision(FName InCollisionName);

protected:
	virtual void BeginPlay() override;

public:
	AEquipment();

	UFUNCTION(BlueprintNativeEvent)
	void OnBeginEquip();
	virtual void OnBeginEquip_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void OnUnequip();
	virtual void OnUnequip_Implementation() {}

public:
	void OnCollision();
	void OffCollision();

	//UFUNCTION()
	//void OnCollision(UAnimMontage* InMontage);

	//UFUNCTION()
	//void OffCollision(UAnimMontage* InMontage, bool Interupt);

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FEquipmentBeginCollision OnEquipmentBeginCollision;
	FEquipmentEndCollision OnEquipmentEndCollision;

protected:
	UPROPERTY()
	ACharacter* OwnerCharacter;
	class UJobComponent* JobComponent;

	TArray<UShapeComponent*> Collisions;

};