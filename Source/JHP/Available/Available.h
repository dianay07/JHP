#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Available.generated.h"

UINTERFACE(MinimalAPI)
class UAvailable : public UInterface
{
	GENERATED_BODY()
};

class UStateComponent;

class JHP_API IAvailable
{
	GENERATED_BODY()

protected:
	virtual void Activate() = 0;
	virtual void Activate(int Index) = 0;
	virtual void DeActivate() = 0;

protected:
	TObjectPtr<ACharacter> OwnerCharacter;
	TObjectPtr<UStateComponent> StateComponent;
};
