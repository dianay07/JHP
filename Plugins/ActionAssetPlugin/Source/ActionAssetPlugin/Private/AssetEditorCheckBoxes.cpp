#include "AssetEditorCheckBoxes.h"

#include "ActionAssetPluginStyle.h"
#include "AssetEditorDetailView.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "IPropertyUtilities.h"
#include "IDetailPropertyRow.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "Animation/AnimMontage.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundWave.h"

void SAssetEditorCheckBoxes::AddProperties(TSharedPtr<IPropertyHandle> InHandle)
{
    uint32 number = 0;
    InHandle->GetNumChildren(number);

    for (uint32 i = 0; i < number; i++)
        InternalDatas.Add(FInternalData(InHandle->GetChildHandle(i)));
}

TSharedRef<SWidget> SAssetEditorCheckBoxes::Draw(bool bBackground)
{
    TSharedPtr<SUniformGridPanel> panel;
    SAssignNew(panel, SUniformGridPanel);
    panel->SetMinDesiredSlotWidth(150);

    for (int32 i = 0; i < InternalDatas.Num(); i++)
    {
        panel->AddSlot(i % 5, i / 5)
            [
                SNew(SCheckBox)
                    .IsChecked(InternalDatas[i].bChecked)
                    .OnCheckStateChanged(this, &SAssetEditorCheckBoxes::OnCheckStateChanged, i)
                    [
                        SNew(STextBlock)
                            .Text(FText::FromString(InternalDatas[i].Name))
                    ]
            ];
    }

    if (bBackground == false)
        return panel.ToSharedRef();

    TSharedPtr<SBorder> border = SNew(SBorder)
        .BorderImage(FActionAssetPluginStyle::Get()->Array_Image.Get())
        [
            panel.ToSharedRef()
        ];

    return border.ToSharedRef();
}

void SAssetEditorCheckBoxes::DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder* InChildrenBuilder)
{
    for (int32 i = 0; i < InternalDatas.Num(); i++)
    {
        if (InternalDatas[i].bChecked == false)
            continue;
       
        TSharedPtr<IPropertyHandle> handle = InPropertyHandle->GetChildHandle(i);
        IDetailPropertyRow& row = InChildrenBuilder->AddProperty(handle.ToSharedRef());

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
    }
}

void SAssetEditorCheckBoxes::SetUtilities(TSharedPtr<IPropertyUtilities> InUtilities)
{
    Utilities = InUtilities;
}

void SAssetEditorCheckBoxes::OnCheckStateChanged(ECheckBoxState InState, int32 InIndex)
{
    InternalDatas[InIndex].bChecked = !InternalDatas[InIndex].bChecked;

    SAssetEditorDetailView::OnRefreshByCheckBoxes();
    
        Utilities->ForceRefresh();
    
    SAssetEditorDetailView::OffRefreshByCheckBoxes();
}

bool SAssetEditorCheckBoxes::CanDraw(TSharedPtr<IPropertyHandle> InHandle, int InCount)
{
    bool bCheck = true;
    bCheck &= InCount > 0;

    int32 index = InHandle->GetIndexInArray();
    bCheck &= index >= 0;
    bCheck &= index < InCount;

    return bCheck;
}

void SAssetEditorCheckBoxes::CheckDefaultObject(int32 InIndex, UObject* InValue)
{
    UObject* val = nullptr;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (val != nullptr && InValue != val)
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultObject(int32 InIndex, const UAnimMontage* InValue)
{
    UObject* val = nullptr;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (InValue != Cast<UAnimMontage>(val))
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultValue(int32 InIndex, int InValue)
{
    int val = 0;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (InValue != val)
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultValue(int32 InIndex, float InValue)
{
    float val = 0.0f;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (InValue != val)
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultValue(int32 InIndex, bool InValue)
{
    bool val = false;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (InValue != val)
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultValue(int32 InIndex, const FVector& InValue)
{
    FVector val = FVector::ZeroVector;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (InValue != val)
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultValue(int32 InIndex, uint8 InValue)
{
    uint8 Type = 0;
    InternalDatas[InIndex].Handle->GetValue(Type);

    if (InValue != Type)
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultObject(int32 InIndex, UFXSystemAsset* InValue)
{
    UObject* val = nullptr;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (val != nullptr && InValue != Cast<UFXSystemAsset>(val))
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultObject(int32 InIndex, USoundWave* InValue)
{
    UObject* val = nullptr;
    InternalDatas[InIndex].Handle->GetValue(val);

    if (val != nullptr && InValue != Cast<USoundWave>(val))
        InternalDatas[InIndex].bChecked = true;
}

void SAssetEditorCheckBoxes::CheckDefaultValue(int32 InIndex, const FText& InValue)
{
    FText val = FText::FromString("");
    InternalDatas[InIndex].Handle->GetValue(val);

    if (InValue.CompareTo(val) == false)
        InternalDatas[InIndex].bChecked = true;
}
