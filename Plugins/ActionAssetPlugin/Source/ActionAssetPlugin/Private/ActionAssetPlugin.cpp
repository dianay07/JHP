#include "ActionAssetPlugin.h"

#include "ActionAssetCommand.h"
#include "ActionAssetContextMenu.h"
#include "ActionAssetPluginStyle.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
IMPLEMENT_MODULE(FActionAssetPluginModule, ActionAssetPlugin)
#define LOCTEXT_NAMESPACE "FActionAssetPluginModule"

void FActionAssetPluginModule::StartupModule()
{
	FActionAssetPluginStyle::Get();

	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type categories = assetTools.RegisterAdvancedAssetCategory("ActionAsset", FText::FromString("JH Custom Menu"));

	ContextMenu = MakeShareable(new FActionAssetContextMenu(categories));
	assetTools.RegisterAssetTypeActions(ContextMenu.ToSharedRef());

	Command = MakeShareable(new FActionAssetCommand());
	Command->Startup();
}

void FActionAssetPluginModule::ShutdownModule()
{
	if (ContextMenu.IsValid())
		ContextMenu.Reset();

	if (Command.IsValid())
		Command.Reset();

	FActionAssetPluginStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE