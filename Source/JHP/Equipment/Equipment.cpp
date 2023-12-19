#include "Equipment.h"

#include "ActionAssetCommand.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

/*
  장비 클래스
 */

/* 소켓이름 받아 캐릭터 매쉬에 장착 */
void AEquipment::AttachTo(FName InSocketName)
{
	// 주인될 캐릭터의 매쉬 찾아 스켈레톤에 있는 무기 포켓에 지정
	AttachToComponent(OwnerCharacter->GetMesh(), 
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), InSocketName);
}

/* 콜리전 부착 */
void AEquipment::AttachToCollision(FName InCollisionName)
{
	// 콜리전 타입의 액터를 모두 찾아 이름 체크 후 캐릭터의 매쉬에 부착
	for (UShapeComponent* collision : Collisions)
	{
		if (collision->GetName() == InCollisionName.ToString())
		{
			collision->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InCollisionName);

			return;
		}
	}
}

/* 기본 설정 */
void AEquipment::BeginPlay()
{
	// 오너 설정
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	// 오너의 콜리전 하위 액터 모두 검색후 저장
	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);

	for (USceneComponent* child : children)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(child);

		if (shape != nullptr)
		{
			// 충돌처리 델리게이트 연결
			shape->OnComponentBeginOverlap.AddDynamic(this, &AEquipment::OnComponentBeginOverlap);
			shape->OnComponentEndOverlap.AddDynamic(this, &AEquipment::OnComponentEndOverlap);

			Collisions.Add(shape);
		}
	}
	OffCollision();

	Super::BeginPlay();
}

AEquipment::AEquipment()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EquipmentSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
	EquipmentSM->SetupAttachment(Root);
}

void AEquipment::OnCollision()
{
	if (OnAttachmentBeginCollision.IsBound())
		OnAttachmentBeginCollision.Broadcast();

	for (UShapeComponent* shape : Collisions)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		if(shape->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		{
			UE_LOG(LogTemp, Error, TEXT("TRUE"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("FALSE"));
		}
	}
		
}

void AEquipment::OffCollision()
{
	if (OnAttachmentEndCollision.IsBound())
		OnAttachmentEndCollision.Broadcast();

	for (UShapeComponent* shape : Collisions)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (shape->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		{
			UE_LOG(LogTemp, Error, TEXT("%s Collisiton Setting : TRUE"), *shape->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%s Collisiton Setting : FALSE"), *shape->GetName());
		}
	}
}

void AEquipment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OwnerCharacter == OtherActor) return;
	if (OwnerCharacter->GetClass() == OtherActor->GetClass()) return;

	if (OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void AEquipment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OwnerCharacter == OtherActor) return;
	if (OwnerCharacter->GetClass() == OtherActor->GetClass()) return;

	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, Cast<ACharacter>(OtherActor));
}
