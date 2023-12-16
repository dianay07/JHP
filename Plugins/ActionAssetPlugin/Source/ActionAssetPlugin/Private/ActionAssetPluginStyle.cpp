#include "ActionAssetPluginStyle.h"

#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

const FName FActionAssetPluginStyle::StyleSetName = "ActionAssetPlugin";

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

const FVector2D Icon20x20(20.0f, 20.0f);
FActionAssetPluginStyle::FActionAssetPluginStyle()
{
    if (StyleSet.IsValid() != false)
        return;

	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));
    StyleSet->SetContentRoot(FPaths::EnginePluginsDir() + "Resources");


    /* TODO :: 이미지 안나옴 */
    FString ImagePath = FPaths::ProjectPluginsDir() + "Resources" + TEXT("Create_Job_Icon.png");
    FSlateImageBrush* ImageBrush = new FSlateImageBrush(ImagePath, Icon20x20);
    StyleSet->Set("ActionAssetPlugin.PluginAction", ImageBrush);
    //StyleSet->Set("ActionAssetPlugin.PluginAction", new IMAGE_BRUSH("Create_Job_Icon"), Icon20x20);

	/*FString path = "";
    path = FPaths::ProjectPluginsDir() / "ActionAssetPlugin" / "Resources";
    RegisterIcon("ToolBar_Icon", path / "Create_Job_Icon.png", FVector2D(40, 20), ToolBar_Icon);
    FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());

    path = FPaths::EngineContentDir() / "Editor" / "Slate" / "Common/Selection.png";
    Array_Image = MakeShareable(new FSlateImageBrush(path, FVector2D(8, 8), FLinearColor(1, 1, 1, 0.1f)));*/
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