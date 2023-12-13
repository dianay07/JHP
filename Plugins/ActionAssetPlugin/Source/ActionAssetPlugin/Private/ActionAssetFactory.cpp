#include "ActionAssetFactory.h"
UActionAssetFactory::UActionAssetFactory()
{
	bCreateNew = true;

	SupportedClass = UObject::StaticClass();
}

UObject* UActionAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObject>(InParent, InClass, InName, Flags);;
}
