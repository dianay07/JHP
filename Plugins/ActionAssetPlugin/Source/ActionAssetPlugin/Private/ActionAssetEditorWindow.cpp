#include "ActionAssetEditorWindow.h"

#include "ActionAttackData.h"
#include "ActionEquipData.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "AssetEditorDetailView.h"
#include "ActionHitData.h"
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
	if (Instance.IsValid() == true)
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
		instance.BindStatic(&SActionEquipData::MakeInstance);
		prop.RegisterCustomPropertyTypeLayout("Draw Animation", instance);
	}

	//// Attack Animation
	{
		FOnGetPropertyTypeCustomizationInstance instance;
		instance.BindStatic(&SActionAttackData::MakeInstance);
		prop.RegisterCustomPropertyTypeLayout("Attack Animation", instance);
	}

	//// Hit Animation
	{
		FOnGetPropertyTypeCustomizationInstance instance;
		instance.BindStatic(&SActionHitData::MakeInstance);
		prop.RegisterCustomPropertyTypeLayout("Hit Animation", instance);
	}

	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("ActionAssetEditorWindow_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			//->Split
			//(
			//	// ��������
			//	FTabManager::NewStack()
			//	->SetSizeCoefficient(0.1f)
			//	->AddTab(FName("TEST"), ETabState::OpenedTab)
			//)
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

		if (ptr.IsValid() == true)
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
			prop.UnregisterCustomPropertyTypeLayout("Draw Animation");
			prop.UnregisterCustomPropertyTypeLayout("Attack Animation");
			prop.UnregisterCustomPropertyTypeLayout("Hit Animation");
		}
	}

	if (LeftArea.IsValid() == true)
		LeftArea.Reset();

	if (DetailsView.IsValid() == true)
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