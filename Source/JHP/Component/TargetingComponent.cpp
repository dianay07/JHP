#include "TargetingComponent.h"

#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "JHP/Character/CCharacterBase.h"
#include "JHP/Character/CEnemy_Basic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// TODO : 1. 거리가 멀어진 경우 타겟팅 취소, 2. 타겟이 죽엇을 경우 타겟팅 전달

UTargetingComponent::UTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	/* Create Component */
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoardComponent"));
}

void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACCharacterBase>(GetOwner());
}

void UTargetingComponent::BeginTarget()
{
	// 검색 범위 설정용 변수
	const FVector start = OwnerCharacter->GetActorLocation();		// 시작 지점
	const FVector end = start;										// 끝 지점
	TArray<AActor*> param;											// 무시대상
	param.Add(OwnerCharacter);

	TArray<FHitResult> Output;										// 결과물 반환받을 배열

	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), start, end, TraceDistance, "Targeting", false, param, EDrawDebugTrace::None, Output, true);
	for (FHitResult hitResult : Output)
	{
		// 본인(플레이어)와 같은 클래스가 아니고 Enemy 이면 ?
		if (hitResult.GetActor()->GetClass() != OwnerCharacter->GetClass() && Cast<ACEnemy_Basic>(hitResult.GetActor()))
		{
			// Target 배열에 저장
			TargetArray.AddUnique(Cast<ACCharacterBase>(hitResult.GetActor()));
		}
	}

	// 최초 탐색, 타겟이 없을 때
	if(CurrentTarget == nullptr)
	{
		CurrentTarget = TargetArray[TargetIndex];
	}
	// 탐색 다시 했을 때, 타겟이 있을 때
	else
	{
		ChangeTarget();
	}

	// 마커 활성화
	ActivateMarker(CurrentTarget);
}

void UTargetingComponent::ChangeTarget()
{
	// 타겟 후보군이 있을 때만
	if(TargetArray.IsEmpty() == false)
	{
		// 배열 크기에서 넘치면 원점으로
		/*if (TargetIndex < TargetArray.Num() - 1)
			TargetIndex++;
		else
			TargetIndex = 0;*/

		GetNearlyCharacter();
	}

	// 현재 타겟 재설정
	CurrentTarget = TargetArray[TargetIndex];
	ActivateMarker(CurrentTarget);
}

void UTargetingComponent::ActivateMarker(ACCharacterBase* InTarget)
{
	// 마커 포지션 = 타겟의 현재 위치 + 캡슐의 절반 높이 * 1.5
	const FVector MarkerPosition = 
		InTarget->GetCapsuleComponent()->GetRelativeLocation() + FVector(0, 0, CurrentTarget->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 1.5f);

	// 위치 세팅
	BillboardComponent->SetRelativeLocation(MarkerPosition);

	// 컴포넌트 활성화
	BillboardComponent->SetHiddenInGame(false);
	BillboardComponent->Activate(true);
}

ACCharacterBase* UTargetingComponent::GetNearlyCharacter()
{
	// 예외
	if (TargetArray.IsEmpty() == true)
		return nullptr;

	// 지역 변수 세팅
	float Angle = 0.0f;
	FVector NormalizedVector = FVector::Zero();
	FVector OwnerForwardVector = FVector::Zero();
	float dotAnswer = 0.0f;

	// 현재 타겟 제거
	TargetArray.Remove(CurrentTarget);

	// 각 크기 검색
	for(int i = 0; i < TargetArray.Num(); i++)
	{
		NormalizedVector = (OwnerCharacter->GetActorLocation() - TargetArray[i]->GetActorLocation()).GetSafeNormal2D();

		OwnerForwardVector = OwnerCharacter->GetActorForwardVector();

		dotAnswer = FVector::DotProduct(NormalizedVector, OwnerForwardVector);

		// 현재 지정된 타겟의 각도와 비교군 비교
		if(dotAnswer >= Angle)
		{
			// 비교 재설정 및 타겟 설정
			Angle = dotAnswer;
			CurrentTarget = TargetArray[i];
			TargetIndex = i;
		}
	}

	return CurrentTarget;
}

void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

