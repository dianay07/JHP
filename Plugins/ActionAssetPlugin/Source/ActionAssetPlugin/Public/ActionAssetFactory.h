#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ActionAssetFactory.generated.h"

UCLASS()
class ACTIONASSETPLUGIN_API UActionAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UActionAssetFactory();

	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};
