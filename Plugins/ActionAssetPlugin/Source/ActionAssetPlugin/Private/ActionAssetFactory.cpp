#include "ActionAssetFactory.h"
#include "ActionAssetPlugin/Data/ActionData.h"
UActionAssetFactory::UActionAssetFactory()
{
	bCreateNew = true;

	SupportedClass = UActionData::StaticClass();
}

UObject* UActionAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UActionData>(InParent, InClass, InName, Flags);;
}
