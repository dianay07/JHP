#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "AssetTypeCategories.h"

class ACTIONASSETPLUGIN_API FActionAssetContextMenu
	: public FAssetTypeActions_Base
{
public:
	FActionAssetContextMenu(EAssetTypeCategories::Type InCategory);

public:
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	uint32 GetCategories() override;

	void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

private:
	EAssetTypeCategories::Type Category;
};
