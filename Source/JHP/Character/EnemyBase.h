#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JHP/Component/StateComponent.h"
#include "EnemyBase.generated.h"

class UBillboardComponent;

UCLASS()
class JHP_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	/* Component */
	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	TObjectPtr<UBillboardComponent> CursorBillboard;

	FORCEINLINE UBillboardComponent* GetCursor() { return CursorBillboard; }

	/* Custom Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStateComponent> StateComponent;

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	/* State Changed */
	virtual void Hitted();
	virtual void Dead();

private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);
};
