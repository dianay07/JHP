#include "AssetEditorDetailView.h"

#include "ActionAttackData.h"
#include "ActionDrawData.h"
#include "AssetEditorCheckBoxes.h"
#include "ActionHitData.h"
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

	
	// DrawAnimation Setting
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Draw", FText::FromString("Draw"));
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
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Attack", FText::FromString("Attack"));
		IDetailPropertyRow& row = category.AddProperty("AttackAnimations", type);

		if (bRefreshByCheckBoxes == false)
		{
			// 스킬 배열에 들어있는 갯수 리턴받아오기
			uint32 count = 0;
			row.GetPropertyHandle()->GetNumChildren(count);

			// 첫 등록시 체크박스 초기화
			SActionAttackData::EmptyCheckBoxes();

			FAttackAnimation data;
			for (uint32 i = 0; i < count; i++)
			{
				// 스킬 배열 핸들 가져와서 각 자식 핸들 가져오기
				TSharedPtr<IPropertyHandle> handle = row.GetPropertyHandle()->GetChildHandle(i);

				// 어떤 핸들을 체크박스에 넣을지 전달
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
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Hit", FText::FromString("Hit"));
		IDetailPropertyRow& row = category.AddProperty("HitAnimations", type);

		if (bRefreshByCheckBoxes == false)
		{
			// 스킬 배열에 들어있는 갯수 리턴받아오기
			uint32 count = 0;
			row.GetPropertyHandle()->GetNumChildren(count);

			// 첫 등록시 체크박스 초기화
			SActionHitData::EmptyCheckBoxes();

			FHitAnimation data;
			for (uint32 i = 0; i < count; i++)
			{
				// 스킬 배열 핸들 가져와서 각 자식 핸들 가져오기
				TSharedPtr<IPropertyHandle> handle = row.GetPropertyHandle()->GetChildHandle(i);

				// 어떤 핸들을 체크박스에 넣을지 전달
				TSharedPtr<SAssetEditorCheckBoxes> checkBoxes = SActionHitData::AddCheckBoxes();
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