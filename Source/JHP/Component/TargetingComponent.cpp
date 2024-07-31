#include "TargetingComponent.h"

#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "JHP/Character/CCharacterBase.h"
#include "JHP/Character/CEnemy_Basic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// TODO : 1. �Ÿ��� �־��� ��� Ÿ���� ���, 2. Ÿ���� �׾��� ��� Ÿ���� ����

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
	// �˻� ���� ������ ����
	const FVector start = OwnerCharacter->GetActorLocation();		// ���� ����
	const FVector end = start;										// �� ����
	TArray<AActor*> param;											// ���ô��
	param.Add(OwnerCharacter);

	TArray<FHitResult> Output;										// ����� ��ȯ���� �迭

	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), start, end, TraceDistance, "Targeting", false, param, EDrawDebugTrace::None, Output, true);
	for (FHitResult hitResult : Output)
	{
		// ����(�÷��̾�)�� ���� Ŭ������ �ƴϰ� Enemy �̸� ?
		if (hitResult.GetActor()->GetClass() != OwnerCharacter->GetClass() && Cast<ACEnemy_Basic>(hitResult.GetActor()))
		{
			// Target �迭�� ����
			TargetArray.AddUnique(Cast<ACCharacterBase>(hitResult.GetActor()));
		}
	}

	// ���� Ž��, Ÿ���� ���� ��
	if(CurrentTarget == nullptr)
	{
		CurrentTarget = TargetArray[TargetIndex];
	}
	// Ž�� �ٽ� ���� ��, Ÿ���� ���� ��
	else
	{
		ChangeTarget();
	}

	// ��Ŀ Ȱ��ȭ
	ActivateMarker(CurrentTarget);
}

void UTargetingComponent::ChangeTarget()
{
	// Ÿ�� �ĺ����� ���� ����
	if(TargetArray.IsEmpty() == false)
	{
		// �迭 ũ�⿡�� ��ġ�� ��������
		/*if (TargetIndex < TargetArray.Num() - 1)
			TargetIndex++;
		else
			TargetIndex = 0;*/

		GetNearlyCharacter();
	}

	// ���� Ÿ�� �缳��
	CurrentTarget = TargetArray[TargetIndex];
	ActivateMarker(CurrentTarget);
}

void UTargetingComponent::ActivateMarker(ACCharacterBase* InTarget)
{
	// ��Ŀ ������ = Ÿ���� ���� ��ġ + ĸ���� ���� ���� * 1.5
	const FVector MarkerPosition = 
		InTarget->GetCapsuleComponent()->GetRelativeLocation() + FVector(0, 0, CurrentTarget->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 1.5f);

	// ��ġ ����
	BillboardComponent->SetRelativeLocation(MarkerPosition);

	// ������Ʈ Ȱ��ȭ
	BillboardComponent->SetHiddenInGame(false);
	BillboardComponent->Activate(true);
}

ACCharacterBase* UTargetingComponent::GetNearlyCharacter()
{
	// ����
	if (TargetArray.IsEmpty() == true)
		return nullptr;

	// ���� ���� ����
	float Angle = 0.0f;
	FVector NormalizedVector = FVector::Zero();
	FVector OwnerForwardVector = FVector::Zero();
	float dotAnswer = 0.0f;

	// ���� Ÿ�� ����
	TargetArray.Remove(CurrentTarget);

	// �� ũ�� �˻�
	for(int i = 0; i < TargetArray.Num(); i++)
	{
		NormalizedVector = (OwnerCharacter->GetActorLocation() - TargetArray[i]->GetActorLocation()).GetSafeNormal2D();

		OwnerForwardVector = OwnerCharacter->GetActorForwardVector();

		dotAnswer = FVector::DotProduct(NormalizedVector, OwnerForwardVector);

		// ���� ������ Ÿ���� ������ �񱳱� ��
		if(dotAnswer >= Angle)
		{
			// �� �缳�� �� Ÿ�� ����
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

