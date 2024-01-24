#include "Equipment.h"

#include "ActionAssetCommand.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ShapeComponent.h"
#include "JHP/Component/JobComponent.h"

/*
  ���� ��� Ŭ����
 */

 /* �⺻ ���� */
void AEquipment::BeginPlay()
{
	// ���� ����
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	JobComponent = Cast<UJobComponent>(OwnerCharacter->GetComponentByClass(UJobComponent::StaticClass()));

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
			shape->SetGenerateOverlapEvents(true);
			Collisions.Add(shape);
		}
	}
	OffCollision();

	Super::BeginPlay();
}

/* �����̸� �޾� ĳ���� �Ž��� ���� */
void AEquipment::AttachTo(USkeletalMeshComponent* Mesh, FName InSocketName)
{
	// ���ε� ĳ������ �Ž� ã�� ���̷��濡 �ִ� ���� ���Ͽ� ����
	AttachToComponent(Mesh,
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

AEquipment::AEquipment()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EquipmentSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
	EquipmentSM->SetupAttachment(Root);
}

void AEquipment::OnCollision()
{
	if (OnEquipmentBeginCollision.IsBound())
		OnEquipmentBeginCollision.Broadcast();

	for (UShapeComponent* shape : Collisions)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AEquipment::OffCollision()
{
	if (OnEquipmentEndCollision.IsBound())
		OnEquipmentEndCollision.Broadcast();

	for (UShapeComponent* shape : Collisions)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

//void AEquipment::OnCollision(UAnimMontage* InMontage)
//{
//	// TODO : Draw ����϶� �۵� �ȵǰ� �ؾ���
//
//	for (UShapeComponent* shape : Collisions)
//	{
//		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
//	}
//
//	UE_LOG(LogTemp, Error, TEXT("OnCollision Activate"));
//}
//
//void AEquipment::OffCollision(UAnimMontage* InMontage, bool Interupt)
//{
//	for (UShapeComponent* shape : Collisions)
//	{
//		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	}
//
//	UE_LOG(LogTemp, Error, TEXT("OffCollision Activate"));
//}

void AEquipment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OwnerCharacter == OtherActor) return;
	if (OwnerCharacter->GetClass() == OtherActor->GetClass()) return;

	UE_LOG(LogTemp, Error, TEXT("AttackActor : %s, AttackWeapon : %s, HitActor : %s, "), *OwnerCharacter->GetName(), *this->GetName(), *OtherActor->GetName());

	if(JobComponent->OnWeaponBeginOverlap.IsBound())
		JobComponent->OnWeaponBeginOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void AEquipment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OwnerCharacter == OtherActor) return;
	if (OwnerCharacter->GetClass() == OtherActor->GetClass()) return;

	if (JobComponent->OnWeaponEndOverlap.IsBound())
		JobComponent->OnWeaponEndOverlap.Broadcast(OwnerCharacter, Cast<ACharacter>(OtherActor));
}
