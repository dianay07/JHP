#include "AssetEditorDetailView.h"

#include "ActionAttackData.h"
#include "ActionDrawData.h"
#include "AssetEditorCheckBoxes.h"
#include "AssetHitData.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "ActionAssetPlugin/Data/ActionData.h"

bool SAssetEditorDetailView::bRefreshByCheckBoxes = false;

TSharedRef<IDetailCustomization> SAssetEditorDetailView::MakeInstance()
{
	return MakeShareable(new SAssetEditorDetailView());
}

void SAssetEditorDetailView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	UClass* type = UActionData::StaticClass();

	DetailBuilder.HideCategory("ActionData");

	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Asset", FText::FromString("Action Data"));
	// DrawAnimation Setting
	{
		IDetailPropertyRow& row = category.AddProperty("DrawAnimation", type);

		if(bRefreshByCheckBoxes == false)
		{
			TSharedPtr<SAssetEditorCheckBoxes> checkBoxes = SActionDrawData::CreateCheckBoxes();
			checkBoxes->AddProperties(row.GetPropertyHandle());

			FDrawAnimation data;

			int32 index = 0;
			checkBoxes->CheckDefaultObject(index++, data.Montage);
			checkBoxes->CheckDefaultValue(index++, data.PlayRate);
			checkBoxes->CheckDefaultObject(index++, data.Sound);
		}
	}

	// Attack Animation Setting
	{
		IDetailPropertyRow& row = category.AddProperty("AttackAnimation", type);

		if (bRefreshByCheckBoxes == false)
		{
			// ��ų �迭�� ����ִ� ���� ���Ϲ޾ƿ���
			uint32 count = 0;
			row.GetPropertyHandle()->GetNumChildren(count);

			// ù ��Ͻ� üũ�ڽ� �ʱ�ȭ
			SActionAttackData::EmptyCheckBoxes();

			FAttackAnimation data;
			for (uint32 i = 0; i < count; i++)
			{
				// ��ų �迭 �ڵ� �����ͼ� �� �ڽ� �ڵ� ��������
				TSharedPtr<IPropertyHandle> handle = row.GetPropertyHandle()->GetChildHandle(i);

				// � �ڵ��� üũ�ڽ��� ������ ����
				TSharedPtr<SAssetEditorCheckBoxes> checkBoxes = SActionAttackData::AddCheckBoxes();
				checkBoxes->AddProperties(handle);

				int32 index = 0;
				checkBoxes->CheckDefaultValue(index++, data.Name);
				checkBoxes->CheckDefaultValue(index++, data.Description);
				checkBoxes->CheckDefaultValue(index++, data.Damage);
				checkBoxes->CheckDefaultObject(index++, data.Montage);
				checkBoxes->CheckDefaultObject(index++, data.Sound);
				checkBoxes->CheckDefaultValue(index++, data.PlayRate);
				checkBoxes->CheckDefaultObject(index++, data.Icon);
				checkBoxes->CheckDefaultObject(index++, data.Effect);
				checkBoxes->CheckDefaultValue(index++, data.EffectLocation);
				checkBoxes->CheckDefaultValue(index++, data.EffectScale);
			}
		} // if
	}

	// Hit Animation Setting
	{
		IDetailPropertyRow& row = category.AddProperty("Hit Animtaion", type);

		if (bRefreshByCheckBoxes == false)
		{
			// ��ų �迭�� ����ִ� ���� ���Ϲ޾ƿ���
			uint32 count = 0;
			row.GetPropertyHandle()->GetNumChildren(count);

			// ù ��Ͻ� üũ�ڽ� �ʱ�ȭ
			SAssetHitData::EmptyCheckBoxes();

			FHitAnimation data;
			for (uint32 i = 0; i < count; i++)
			{
				// ��ų �迭 �ڵ� �����ͼ� �� �ڽ� �ڵ� ��������
				TSharedPtr<IPropertyHandle> handle = row.GetPropertyHandle()->GetChildHandle(i);

				// � �ڵ��� üũ�ڽ��� ������ ����
				TSharedPtr<SAssetEditorCheckBoxes> checkBoxes = SAssetHitData::AddCheckBoxes();
				checkBoxes->AddProperties(handle);

				int32 index = 0;
				checkBoxes->CheckDefaultValue(index++, data.PlayRate);
				checkBoxes->CheckDefaultObject(index++, data.Sound);
				checkBoxes->CheckDefaultObject(index++, data.Effect);
				checkBoxes->CheckDefaultValue(index++, data.EffectLocation);
				checkBoxes->CheckDefaultValue(index++, data.EffectScale);
			}
		} // if
	}
}