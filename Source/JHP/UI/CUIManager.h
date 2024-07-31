#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUIManager.generated.h"

/*
 *	UI Manager
 *	HUD와 별개
 *	특정 키 입력으로 팝업 UI들을 관리
 */

UCLASS()
class JHP_API UCUIManager : public UUserWidget
{
	GENERATED_BODY()

public:
	UCUIManager(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void ShowSkillBook();
	void ShowInventory();
	void ShowStatus();

private:
	/* 소속 UI들의 TSubClass */

};
