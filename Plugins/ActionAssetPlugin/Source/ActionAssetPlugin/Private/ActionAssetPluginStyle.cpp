#include "ActionAssetPluginStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

const FName FActionAssetPluginStyle::StyleSetName = "WeaponStyle";

TSharedPtr<FActionAssetPluginStyle> FActionAssetPluginStyle::Instance = nullptr;

TSharedRef<FActionAssetPluginStyle> FActionAssetPluginStyle::Get()
{
    if (Instance == nullptr)
        Instance = MakeShareable(new FActionAssetPluginStyle());

    return Instance.ToSharedRef();
}

void FActionAssetPluginStyle::Shutdown()
{
    if (Instance.IsValid())
        Instance.Reset();
}

FActionAssetPluginStyle::FActionAssetPluginStyle()
{
    StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));


    FString path = "";

    path = FPaths::ProjectPluginsDir() / "Weapon" / "Resources";
    RegisterIcon("ToolBar_Icon", path / "Create_Job_Icon.png", FVector2D(40, 40), ToolBar_Icon);

    FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());


    path = FPaths::EngineContentDir() / "Editor" / "Slate" / "Common/Selection.png";
    Array_Image = MakeShareable(new FSlateImageBrush(path, FVector2D(8, 8), FLinearColor(1, 1, 1, 0.1f)));
}

FActionAssetPluginStyle::~FActionAssetPluginStyle()
{
    if (Array_Image.IsValid())
        Array_Image.Reset();

    if (StyleSet.IsValid() == false) return;

    FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
    StyleSet.Reset();
}

void FActionAssetPluginStyle::RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon)
{
    FSlateImageBrush* brush = new FSlateImageBrush(InPath, InIconSize);

    FString name = StyleSetName.ToString() + "." + InName;
    StyleSet->Set(FName(name), brush);

    OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(name));
}