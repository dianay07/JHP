#include "CUIManager.h"

// TODO : �� UI ����, �̿� �̸� ��� ���� �����ϰ�

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
