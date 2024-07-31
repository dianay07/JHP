#include "Grid.h"

#include "Components/InstancedStaticMeshComponent.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	RootComponent = InstancedStaticMeshComponent;

}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	// 십자 모양으로 5개의 StaticMesh 배치
	InstancedStaticMeshComponent->AddInstance(FTransform(FRotator::ZeroRotator, FVector(0.0f, 0.0f, 0.0f), FVector(1.0f)));
	InstancedStaticMeshComponent->AddInstance(FTransform(FRotator::ZeroRotator, FVector(100.0f, 0.0f, 0.0f), FVector(1.0f)));
	InstancedStaticMeshComponent->AddInstance(FTransform(FRotator::ZeroRotator, FVector(-100.0f, 0.0f, 0.0f), FVector(1.0f)));
	InstancedStaticMeshComponent->AddInstance(FTransform(FRotator::ZeroRotator, FVector(0.0f, 100.0f, 0.0f), FVector(1.0f)));
	InstancedStaticMeshComponent->AddInstance(FTransform(FRotator::ZeroRotator, FVector(0.0f, -100.0f, 0.0f), FVector(1.0f)));
	
}

void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

