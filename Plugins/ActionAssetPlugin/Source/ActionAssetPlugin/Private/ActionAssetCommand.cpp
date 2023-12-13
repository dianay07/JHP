#include "ActionAssetCommand.h"

#include "ActionAssetPluginStyle.h"
#include "EditorStyleSet.h"
#include "LevelEditor.h"

FActionAssetCommand::FActionAssetCommand()
	: TCommands("Toolbar_Buttons", FText::FromString(""), NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FActionAssetCommand::~FActionAssetCommand()
{
	if (Command.IsValid())
		Command.Reset();

	if (Extender.IsValid())
		Extender.Reset();
}

void FActionAssetCommand::Startup()
{
	FActionAssetCommand::RegisterCommands();

	Extender = MakeShareable(new FExtender());

	FToolBarExtensionDelegate toolbar = FToolBarExtensionDelegate::CreateRaw(this, &FActionAssetCommand::AddToolBar);
	Extender->AddToolBarExtension("ActionAsset", EExtensionHook::After, Command, toolbar);//Settings, PluginTools, Contents

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FActionAssetCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(Id, "ActionAsset", "", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE


	FExecuteAction action;
	action.BindRaw(this, &FActionAssetCommand::OnClicked);

	Command->MapAction(Id, action, FCanExecuteAction());
}

void FActionAssetCommand::AddToolBar(FToolBarBuilder& InBuilder)
{
	FString name = TEXT("ActionAsset");

	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton(Id, NAME_None, FText::FromString(name), FText::FromString("Action Asset Editor"), FActionAssetPluginStyle::Get()->ToolBar_Icon, NAME_None);
}

void FActionAssetCommand::OnClicked()
{
	//FWeaponAssetEditor::OpenWindow();
}