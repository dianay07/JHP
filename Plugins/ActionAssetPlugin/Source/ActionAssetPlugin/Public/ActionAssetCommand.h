#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class ACTIONASSETPLUGIN_API FActionAssetCommand
	: public TCommands<FActionAssetCommand>
{
public:
	FActionAssetCommand();
	~FActionAssetCommand();

	void Startup();

public:
	virtual void RegisterCommands() override;

private:
	TSharedPtr<FExtender> Extender;

public:
	TSharedPtr<FUICommandList> Command;
	TSharedPtr<FUICommandInfo> Id;

private:
	void AddToolBar(FToolBarBuilder& InBuilder);
	void RegisterMenu();
	void OnClicked();
};
