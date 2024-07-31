#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUIManager.generated.h"

/*
 *	UI Manager
 *	HUD�� ����
 *	Ư�� Ű �Է����� �˾� UI���� ����
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
	/* �Ҽ� UI���� TSubClass */

};
