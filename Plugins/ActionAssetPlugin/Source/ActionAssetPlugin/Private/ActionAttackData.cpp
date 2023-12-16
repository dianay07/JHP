#include "ActionAttackData.h"

#include "ActionAssetPluginStyle.h"
#include "AssetEditorCheckBoxes.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailPropertyRow.h"

TArray<TSharedPtr<SAssetEditorCheckBoxes>> SActionAttackData::CheckBoxes;

TSharedRef<IPropertyTypeCustomization> SActionAttackData::MakeInstance()
{
	return MakeShareable(new SActionAttackData());
}

TSharedPtr<SAssetEditorCheckBoxes> SActionAttackData::AddCheckBoxes()
{
	TSharedPtr<SAssetEditorCheckBoxes> checkBoxes = MakeShareable(new SAssetEditorCheckBoxes());
	int32 index = CheckBoxes.Add(checkBoxes);

	return CheckBoxes[index];
}

void SActionAttackData::EmptyCheckBoxes()
{
	for (TSharedPtr<SAssetEditorCheckBoxes> ptr : CheckBoxes)
	{
		if (ptr.IsValid())
			ptr.Reset();
	}

	CheckBoxes.Empty();
}

void SActionAttackData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow,
	IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	if (SAssetEditorCheckBoxes::CanDraw(InPropertyHandle, CheckBoxes.Num()) == false)
	{
		InHeaderRow
			.NameContent()
			[
				InPropertyHandle->CreatePropertyNameWidget()
			]
			.ValueContent()
			.MinDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.X)
			.MaxDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.Y)
			[
				InPropertyHandle->CreatePropertyValueWidget()
			];

		return;
	}

	int32 index = InPropertyHandle->GetIndexInArray();
	CheckBoxes[index]->SetUtilities(InCustomizationUtils.GetPropertyUtilities());

	FString name = InPropertyHandle->GetPropertyDisplayName().ToString();
	name = "Attack Animation - " + name;

	InHeaderRow
		.NameContent()
		[
			SNew(SBorder)
				.BorderImage(FActionAssetPluginStyle::Get()->Array_Image.Get())
				[
					InPropertyHandle->CreatePropertyNameWidget(FText::FromString(name))
				]
		]
		.ValueContent()
		.MinDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.X)
		.MaxDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.Y)
		[
			CheckBoxes[index]->Draw(true)
		];
}

void SActionAttackData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder,
	IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	if (SAssetEditorCheckBoxes::CanDraw(InPropertyHandle, CheckBoxes.Num()) == false)
	{
		uint32 number = 0;
		InPropertyHandle->GetNumChildren(number);

		for (uint32 i = 0; i < number; i++)
		{
			TSharedPtr<IPropertyHandle> handle = InPropertyHandle->GetChildHandle(i);
			IDetailPropertyRow& row = InChildBuilder.AddProperty(handle.ToSharedRef());

			TSharedPtr<SWidget> name;
			TSharedPtr<SWidget> value;

			row.GetDefaultWidgets(name, value);

			row.CustomWidget()
				.NameContent()
				[
					name.ToSharedRef()
				]
				.ValueContent()
				.MinDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.X)
				.MaxDesiredWidth(FActionAssetPluginStyle::Get()->DesiredWidth.Y)
				[
					value.ToSharedRef()
				];
		}//for(i)

		return;
	}

	int32 index = InPropertyHandle->GetIndexInArray();
	CheckBoxes[index]->DrawProperties(InPropertyHandle, &InChildBuilder);
}
