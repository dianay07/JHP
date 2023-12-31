#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class ACTIONASSETPLUGIN_API SAssetEditorDetailView
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

public:
	static void OnRefreshByCheckBoxes() { bRefreshByCheckBoxes = true; }
	static void OffRefreshByCheckBoxes() { bRefreshByCheckBoxes = false; }

private:
	static bool bRefreshByCheckBoxes;
};
