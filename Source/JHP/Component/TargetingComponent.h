#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

class ACCharacterBase;
class ACEnemy_Basic;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JHP_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetingComponent();

protected:
	virtual void BeginPlay() override;

protected:
	/* BillBoard Component */
	UPROPERTY(VisibleAnywhere, Category = "Settings")
	TObjectPtr<UBillboardComponent> BillboardComponent;

	/* Ÿ���� ���� ���� */
	UPROPERTY(VisibleAnywhere, Category = "Settings")
	float TraceDistance = 2000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Settings")
	float FinishAngle = 200.0f;

	UPROPERTY(VisibleAnywhere, Category = "Settings")
	float InterpSpeed = 5.0f;

public:
	/* Ÿ���� ���� */
	void BeginTarget();										// Ÿ���� ���� ����
	// ĳ���Ͱ� �ٶ󺸴� �������� ���� ���� Ÿ�ٵ� ���͸� ������ ���� ����� ���� Ÿ������ ����
	void ChangeTarget();									// Ÿ�� ����
	void ActivateMarker(ACCharacterBase* InTarget);			// Ÿ���� ��ũ ǥ��


	/* Getter */
	FORCEINLINE ACCharacterBase* GetCurrentTarget() { return CurrentTarget; }

	/* Math Function */
private:
	ACCharacterBase* GetNearlyCharacter();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<ACCharacterBase> OwnerCharacter;					// ������Ʈ ����
	int TargetIndex = 0;
	TObjectPtr<ACCharacterBase> CurrentTarget = nullptr;		// ���� Ÿ����

	TArray<ACCharacterBase*> TargetArray;						// Ÿ�� �迭
};
