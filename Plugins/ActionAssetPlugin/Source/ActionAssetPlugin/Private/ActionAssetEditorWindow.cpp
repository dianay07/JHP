#include "ActionAssetEditorWindow.h"

#include "ActionDrawData.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "AssetEditorDetailView.h"
#include "ActionAssetPlugin/Data/ActionData.h"

const FName FActionAssetEditorWindow::EditorName = "AssetEditorWindow";
const FName FActionAssetEditorWindow::LeftAreaTabId = "LeftArea";
const FName FActionAssetEditorWindow::DetailTabId = "Details";

TSharedPtr<FActionAssetEditorWindow> FActionAssetEditorWindow::Instance = nullptr;

void FActionAssetEditorWindow::OpenWindow(FString InAssetName)
{
	if (Instance.IsValid())
	{
		if (Instance->LeftArea.IsValid())
		{
			FAssetRowDataPtr ptr = nullptr;

			if (InAssetName.Len() > 0)
				ptr = Instance->LeftArea->GetRowDataPtrByName(InAssetName);

			if (ptr.IsValid() == false)
				ptr = Instance->LeftArea->GetFirstDataPtr();

			Instance->LeftArea->SelectDataPtr(ptr->Asset);

			return;
		}

		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FActionAssetEditorWindow());
	Instance->Open(InAssetName);
}

void FActionAssetEditorWindow::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
}

void FActionAssetEditorWindow::Open(FString InAssetName)
{
	LeftArea = SNew(SAssetEditorLeftArea)
		.OnSelectedItem(this, &FActionAssetEditorWindow::OnListViewSelectedItem);

	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// �����Ϻ� �⺻������ ����
	{
		FDetailsViewArgs args;
		args.bUpdatesFromSelection = false;
		args.bLockable = false;
		args.bAllowSearch = true;
		args.NameAreaSettings = FDetailsViewArgs::HideNameArea;
		args.ViewIdentifier = "AssetEditorDetailsView";
		DetailsView = prop.CreateDetailView(args);

		// FOnGetDetailCustomizationInstance�� �߰��� Ŀ���� â�� ���
		FOnGetDetailCustomizationInstance detailView;
		detailView.BindStatic(&SAssetEditorDetailView::MakeInstance);
		DetailsView->SetGenericLayoutDetailsDelegate(detailView);
	}

	// Draw Animation
	{
		FOnGetPropertyTypeCustomizationInstance instance;
		instance.BindStatic(&SActionDrawData::MakeInstance);
		prop.RegisterCustomPropertyTypeLayout("DrawData", instance);
	}

	//// SkillData
	//{
	//	FOnGetPropertyTypeCustomizationInstance instance;
	//	instance.BindStatic(&SJobSkillData::MakeInstance);
	//	prop.RegisterCustomPropertyTypeLayout("SkillData", instance);
	//}

	//// HitData
	//{
	//	FOnGetPropertyTypeCustomizationInstance instance;
	//	instance.BindStatic(&SJobSkillDamageData::MakeInstance);
	//	prop.RegisterCustomPropertyTypeLayout("SkillDamageData", instance);
	//}


	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("ActionAssetEditorWindow_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				// ��������
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(FName("TEST"), ETabState::OpenedTab)
			)
			->Split
			(
				// ��������
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.175f)
					->AddTab(LeftAreaTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.725f)
					->AddTab(DetailTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
			)
		);

	UActionData* asset = nullptr;
	if (InAssetName.Len() > 0)
	{
		FAssetRowDataPtr ptr = LeftArea->GetRowDataPtrByName(InAssetName);

		if (LeftArea->SelectedRowDataPtrName() == InAssetName)
			return;

		if (ptr.IsValid())
			asset = ptr->Asset;
	}

	if (asset == nullptr)
		asset = LeftArea->GetFirstDataPtr()->Asset;

	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, layout, true, true, asset);
	//DetailsView->SetObject(asset);
	LeftArea->SelectDataPtr(asset);
}

bool FActionAssetEditorWindow::OnRequestClose()
{
	if (DetailsView != nullptr)
	{
		// â�� ���� �����ϰٴ� �ҷ��� �����Ϻ� �ȿ� �ּ��� �����϶�� ���
		if (!!GEditor && !!GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetEditingObject(), this);

		// �� â������ Ŀ������ â�� �������� ����
		if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
		{
			FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			prop.UnregisterCustomPropertyTypeLayout("DrawData");
			//prop.UnregisterCustomPropertyTypeLayout("SkillData");
			//prop.UnregisterCustomPropertyTypeLayout("SkillDamageData");
		}
	}

	if (LeftArea.IsValid())
		LeftArea.Reset();

	if (DetailsView.IsValid())
		DetailsView.Reset();

	return true;
}

void FActionAssetEditorWindow::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab;
	tab.BindSP(this, &FActionAssetEditorWindow::Spawn_LeftAreaTab);
	TabManager->RegisterTabSpawner(LeftAreaTabId, tab);

	FOnSpawnTab tab2;
	tab2.BindSP(this, &FActionAssetEditorWindow::Spawn_DetailsViewTab);
	TabManager->RegisterTabSpawner(DetailTabId, tab2);
}

TSharedRef<SDockTab> FActionAssetEditorWindow::Spawn_LeftAreaTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			LeftArea.ToSharedRef()
		];
}

TSharedRef<SDockTab> FActionAssetEditorWindow::Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];
}

void FActionAssetEditorWindow::OnListViewSelectedItem(FAssetRowDataPtr InDataPtr)
{
	if (InDataPtr == nullptr)
		return;

	// ���� �������� �ּ� ����
	if (GetEditingObject() != nullptr)
		RemoveEditingObject(GetEditingObject());

	AddEditingObject(InDataPtr->Asset);				// �ٽ� ������ â ���
	DetailsView->SetObject(InDataPtr->Asset);		// â�� ������ �信 ������ �ּ� ���
}

FName FActionAssetEditorWindow::GetToolkitFName() const
{
	return EditorName;
}

FText FActionAssetEditorWindow::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FActionAssetEditorWindow::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

FLinearColor FActionAssetEditorWindow::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}

FReply FActionAssetEditorWindow::OnClicked()
{
	return FReply::Handled();
}