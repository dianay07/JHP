#pragma once

#include "CoreMinimal.h"
#include "CCharacterBase.h"
#include "CInteractiveChar.generated.h"

UCLASS()
class JHP_API ACInteractiveChar : public ACCharacterBase
{
	GENERATED_BODY()

public:
	ACInteractiveChar();

protected:
	virtual void BeginPlay() override;

	/* Components */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBillboardComponent> BillboardComponent;

public:
	virtual void Tick(float DeltaTime) override;

public:
	bool IsEnemy = false;
	FORCEINLINE bool GetIsEnemy() { return IsEnemy; }

};
