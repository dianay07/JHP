#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FActionAssetContextMenu;
class FActionAssetCommand;

class FActionAssetPluginModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FActionAssetContextMenu> ContextMenu;
	TSharedPtr<FActionAssetCommand> Command;
};
