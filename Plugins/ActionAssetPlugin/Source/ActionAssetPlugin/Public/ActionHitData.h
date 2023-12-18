#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class SAssetEditorCheckBoxes;

class ACTIONASSETPLUGIN_API SActionHitData
	: public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	static TSharedPtr<SAssetEditorCheckBoxes> AddCheckBoxes();
	static void EmptyCheckBoxes();

	void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;
	void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;

private:
	static TArray<TSharedPtr<SAssetEditorCheckBoxes>> CheckBoxes;
};
