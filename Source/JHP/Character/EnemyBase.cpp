#include "EnemyBase.h"

#include "JHP/Component/StateComponent.h"

AEnemyBase::AEnemyBase()
{
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("State Component"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	StateComponent->OnStateTypeChanged.BindUObject(this, &AEnemyBase::OnStateTypeChanged);
}

void AEnemyBase::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Hitted: Hitted(); break;
		case EStateType::Dead: Dead(); break;
	}
}

void AEnemyBase::Hitted()
{
}

void AEnemyBase::Dead()
{
}