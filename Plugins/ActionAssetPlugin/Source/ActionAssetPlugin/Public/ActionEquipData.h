#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class SAssetEditorCheckBoxes;

class ACTIONASSETPLUGIN_API SActionEquipData
	: public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	static TSharedPtr<SAssetEditorCheckBoxes> CreateCheckBoxes();

	void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;
	void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;

private:
	static TSharedPtr<SAssetEditorCheckBoxes> CheckBoxes;
};
