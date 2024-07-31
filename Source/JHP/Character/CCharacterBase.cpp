#include "CCharacterBase.h"

ACCharacterBase::ACCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 기본 이름
	ObjectName = "DefaultName";

	// 정위치 바라보게
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	/* State 컴포넌트 생성 */
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("State Component"));
}

ACCharacterBase::ACCharacterBase(FString Name)
	: ObjectName(Name)
{
}

void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacterBase::StateTypeChanged(EStateType PrevType, EStateType InType)
{
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

