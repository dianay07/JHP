#include "ActionDrawData.h"

#include "DetailWidgetRow.h"
#include "ActionAssetPluginStyle.h"
#include "AssetEditorCheckBoxes.h"

TSharedPtr<SAssetEditorCheckBoxes> SActionDrawData::CheckBoxes;

TSharedRef<IPropertyTypeCustomization> SActionDrawData::MakeInstance()
{
	return MakeShareable(new SActionDrawData());
}

TSharedPtr<SAssetEditorCheckBoxes> SActionDrawData::CreateCheckBoxes()
{
	if (CheckBoxes.IsValid())
	{
		CheckBoxes.Reset();
		CheckBoxes = nullptr;
	}

	return CheckBoxes = MakeShareable(new SAssetEditorCheckBoxes());
}

void SActionDrawData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow,
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

void SActionDrawData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder,
	IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->DrawProperties(InPropertyHandle, &InChildBuilder);
}
