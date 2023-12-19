#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttachmentBeginCollision);
DECLARE_MULTICAST_DELEGATE(FAttachmentEndCollision);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, AActor*, class ACharacter*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAttachmentEndOverlap, class ACharacter*, class ACharacter*);

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
	void AttachTo(FName InSocketName);

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

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FAttachmentBeginCollision OnAttachmentBeginCollision;
	FAttachmentEndCollision OnAttachmentEndCollision;

	FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	FAttachmentEndOverlap OnAttachmentEndOverlap;

protected:
	UPROPERTY()
	ACharacter* OwnerCharacter;
	TArray<UShapeComponent*> Collisions;

};