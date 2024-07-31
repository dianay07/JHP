#include "CUIManager.h"

// TODO : 각 UI 생성, 이왕 이면 상속 구조 가능하게

UCUIManager::UCUIManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCUIManager::NativeConstruct()
{
	Super::NativeConstruct();

	AddToViewport();
}

void UCUIManager::ShowSkillBook()
{
}

void UCUIManager::ShowInventory()
{
}

void UCUIManager::ShowStatus()
{
}
