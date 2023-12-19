#include "Equipment.h"

#include "ActionAssetCommand.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

/*
  ��� Ŭ����
 */

/* �����̸� �޾� ĳ���� �Ž��� ���� */
void AEquipment::AttachTo(FName InSocketName)
{
	// ���ε� ĳ������ �Ž� ã�� ���̷��濡 �ִ� ���� ���Ͽ� ����
	AttachToComponent(OwnerCharacter->GetMesh(), 
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), InSocketName);
}

/* �ݸ��� ���� */
void AEquipment::AttachToCollision(FName InCollisionName)
{
	// �ݸ��� Ÿ���� ���͸� ��� ã�� �̸� üũ �� ĳ������ �Ž��� ����
	for (UShapeComponent* collision : Collisions)
	{
		if (collision->GetName() == InCollisionName.ToString())
		{
			collision->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InCollisionName);

			return;
		}
	}
}

/* �⺻ ���� */
void AEquipment::BeginPlay()
{
	// ���� ����
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	// ������ �ݸ��� ���� ���� ��� �˻��� ����
	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);

	for (USceneComponent* child : children)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(child);

		if (shape != nullptr)
		{
			// �浹ó�� ��������Ʈ ����
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
