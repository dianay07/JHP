#include "ActionAssetContextMenu.h"
FActionAssetContextMenu::FActionAssetContextMenu(EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}

FText FActionAssetContextMenu::GetName() const
{
	return FText::FromString("DataAsset");
}

UClass* FActionAssetContextMenu::GetSupportedClass() const
{
	return UClass::StaticClass();
}

FColor FActionAssetContextMenu::GetTypeColor() const
{
	return FColor::Red;
}

uint32 FActionAssetContextMenu::GetCategories()
{
	return Category;
}

void FActionAssetContextMenu::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	if (InObjects.Num() < 1)
		return;

	//FWeaponAssetEditor::OpenWindow(InObjects[0]->GetName());
}