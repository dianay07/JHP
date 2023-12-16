#include "ActionAssetCommand.h"

#include "ActionAssetEditorWindow.h"
#include "ActionAssetPluginStyle.h"
#include "EditorStyleSet.h"
#include "ToolMenus.h"
#include "LevelEditor.h"

FActionAssetCommand::FActionAssetCommand()
	: TCommands("Toolbar_Buttons", FText::FromString(""), NAME_None, FAppStyle::GetAppStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FActionAssetCommand::~FActionAssetCommand()
{
	if (Command.IsValid())
		Command.Reset();

	if (Extender.IsValid())
		Extender.Reset();

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

void FActionAssetCommand::Startup()
{
	FActionAssetCommand::RegisterCommands();

	Extender = MakeShareable(new FExtender());

	FToolBarExtensionDelegate toolbar = FToolBarExtensionDelegate::CreateRaw(this, &FActionAssetCommand::AddToolBar);
	Extender->AddToolBarExtension("Contents", EExtensionHook::After, Command, toolbar);//Settings, PluginTools, Contents

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FActionAssetCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(Id, "ActionAsset", "", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	Command->MapAction(
		Id,
		FExecuteAction::CreateRaw(this, &FActionAssetCommand::OnClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FActionAssetCommand::RegisterMenu));
}

void FActionAssetCommand::AddToolBar(FToolBarBuilder& InBuilder)
{
	FString name = TEXT("ActionAsset");

	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton(Id, NAME_None, FText::FromString(name), FText::FromString("Action Asset Editor"), FActionAssetPluginStyle::Get()->ToolBar_Icon, NAME_None);
}

void FActionAssetCommand::RegisterMenu()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(Id, Command);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(Id));
				Entry.SetCommandList(Command);
			}
		}
	}
}

void FActionAssetCommand::OnClicked()
{
	FActionAssetEditorWindow::OpenWindow();
}