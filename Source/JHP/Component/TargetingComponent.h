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

	/* 타겟팅 설정 변수 */
	UPROPERTY(VisibleAnywhere, Category = "Settings")
	float TraceDistance = 2000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Settings")
	float FinishAngle = 200.0f;

	UPROPERTY(VisibleAnywhere, Category = "Settings")
	float InterpSpeed = 5.0f;

public:
	/* 타겟팅 동작 */
	void BeginTarget();										// 타겟팅 최초 시작
	// 캐릭터가 바라보는 정면으로 부터 현재 타겟된 액터를 제외한 가장 가까운 적을 타겟으로 지정
	void ChangeTarget();									// 타겟 변경
	void ActivateMarker(ACCharacterBase* InTarget);			// 타겟팅 마크 표시


	/* Getter */
	FORCEINLINE ACCharacterBase* GetCurrentTarget() { return CurrentTarget; }

	/* Math Function */
private:
	ACCharacterBase* GetNearlyCharacter();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<ACCharacterBase> OwnerCharacter;					// 컴포넌트 오너
	int TargetIndex = 0;
	TObjectPtr<ACCharacterBase> CurrentTarget = nullptr;		// 현재 타겟팅

	TArray<ACCharacterBase*> TargetArray;						// 타겟 배열
};
