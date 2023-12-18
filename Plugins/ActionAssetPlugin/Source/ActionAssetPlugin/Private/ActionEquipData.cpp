#include "ActionEquipData.h"

#include "DetailWidgetRow.h"
#include "ActionAssetPluginStyle.h"
#include "AssetEditorCheckBoxes.h"

TSharedPtr<SAssetEditorCheckBoxes> SActionEquipData::CheckBoxes;

TSharedRef<IPropertyTypeCustomization> SActionEquipData::MakeInstance()
{
	return MakeShareable(new SActionEquipData());
}

TSharedPtr<SAssetEditorCheckBoxes> SActionEquipData::CreateCheckBoxes()
{
	if (CheckBoxes.IsValid())
	{
		CheckBoxes.Reset();
		CheckBoxes = nullptr;
	}

	return CheckBoxes = MakeShareable(new SAssetEditorCheckBoxes());
}

void SActionEquipData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow,
	IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->SetUtilities(InCustomizationUtils.GetPropertyUtilities());

	InHeaderRow
		.NameContent()
		[
			InPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.X)
		.MaxDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.Y)
		[
			CheckBoxes->Draw()
		];
}

void SActionEquipData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder,
	IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->DrawProperties(InPropertyHandle, &InChildBuilder);
}
