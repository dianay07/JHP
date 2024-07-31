#include "JHPCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "JHP/Component/StateComponent.h"
#include "JHP/Component/JobComponent.h"
#include "JHP/Component/EquipComponent.h"
#include "JHP/Component/TargetingComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "JHP/Equipment/Equipment.h"
#include "JHP/UI/CUIManager.h"
#include "Kismet/KismetSystemLibrary.h"

//////////////////////////////////////////////////////////////////////////
// AJHPCharacter

AJHPCharacter::AJHPCharacter()
{
	ObjectName = "Playable Character";

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	/* Component */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 700.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	//StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("State Component"));
	JobComponent = CreateDefaultSubobject<UJobComponent>(TEXT("Job Component"));
	EquipComponent = CreateDefaultSubobject<UEquipComponent>(TEXT("Equip Component"));
	TargetComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetComponent"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	/* AnimInstance */
	TSubclassOf<UAnimInstance> instance = ConstructorHelpers::FClassFinder<UAnimInstance>(TEXT("/Script/Engine.AnimBlueprint'/Game/01_Character/ABP_Character.ABP_Character_C'")).Class;
	if(instance != nullptr)
	{
		GetMesh()->SetAnimClass(instance);
	}

	//static ConstructorHelpers::FObjectFinder<UInputAction> InputActionVaultRef(TEXT(""));
	//if(InputActionVaultRef.Object)
	//{
	//	VaultAction = InputActionVaultRef.Object;
	//}

	/* UI */
	static ConstructorHelpers::FClassFinder<UCUIManager> WB_UIMANAGER(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/06_UI/BP_CUIManager.BP_CUIManager_C'"));
	if(WB_UIMANAGER.Succeeded())
	{
		UIManagerClass = WB_UIMANAGER.Class;
	}
}

void AJHPCharacter::ControlCamera(bool Input)
{
	if(Input)
	{
		bUseControllerRotationYaw = true;
		CameraComponent->bUsePawnControlRotation = true;
	}
	else
	{
		bUseControllerRotationYaw = false;
		CameraComponent->bUsePawnControlRotation = false;
	}
}

void AJHPCharacter::BeginPlay()
{
	Super::BeginPlay();


	/* Input MappingContext 세팅 */
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	/* UI Manager 세팅 */
	UIManager = Cast<UCUIManager>(CreateWidget(GetWorld(), UIManagerClass));
	UIManager->AddToViewport();


	JobComponent->ChangeJob(EJob::Warrior);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJHPCharacter::SetMovementMode()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	SetActorEnableCollision(true);
	CanWarp = false;
	VaultLandPos = FVector(0, 0, 20000.0f);
}

void AJHPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJHPCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJHPCharacter::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, TargetComponent.Get(), &UTargetingComponent::BeginTarget);
		EnhancedInputComponent->BindAction(VaultAction, ETriggerEvent::Started, this, &AJHPCharacter::Vault);

		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Ongoing, this, &AJHPCharacter::StartGuard);
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Completed, this, &AJHPCharacter::StopGuard);

		// 키 변경 코드 : InputAction 의 키가 그대로 바뀜
		//DefaultMappingContext->UnmapAllKeysFromAction(AttackAction);
		//DefaultMappingContext->MapKey(AttackAction, EKeys::T);
	}
}

void AJHPCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (GetStateComponent()->IsIdleMode())
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void AJHPCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AJHPCharacter::Attack()
{
	if (GetStateComponent()->InBattle == false)
	{
		// 전투 상태로 변경, 무기 장착 애니메이션 재생
		OnEnterBattleCommand.Broadcast();
		ControlCamera(true);
	}
	else if(GetStateComponent()->InBattle == true)
	{
		// 공격할때 인덱스 값으로 공격 모션 재생
		GetJobComponent()->DoAction();
		//OnPlayAttackMontage.Broadcast(GetJobComponent()->GetAttackAnimationIndex());
	}
}

void AJHPCharacter::StartGuard()
{
	// 상태를 가드로 전환
	GetStateComponent()->SetStateGuard();
}

void AJHPCharacter::StopGuard()
{
}

void AJHPCharacter::Vault()
{
	FCollisionShape SweepSphere = FCollisionShape::MakeSphere(5.0f);
	TArray<FHitResult> Out;

	FVector ActorLocation = this->GetActorLocation();
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	for(int i = 0; i < 3; i++)
	{
		FVector SweepStartLocation = ActorLocation + FVector(0, 0, (i * 30));
		FVector SweepEndLocation = SweepStartLocation + (GetActorForwardVector() * 180.0f);

		//GetWorld()->SweepMultiByChannel(Out, SweepStartLoaction, FVector::Zero(), FQuat::Identity, ECollisionChannel::ECC_Visibility, SweepSphere);

		if(UKismetSystemLibrary::SphereTraceMulti(GetWorld(), SweepStartLocation, SweepEndLocation, 5.0f,
			UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoreActors,
			EDrawDebugTrace::ForDuration, Out, true))
		{
			for(int j = 0; j < 6; j++)
			{
				FVector Start2 = Out[0].Location + FVector(0.0f, 0.0f, 100.0f) + GetActorForwardVector() * (j * 50);
				FVector End2 = Start2 - FVector(0.0f, 0.0f, 100.0f);

				TArray<FHitResult> Out2;

				if(UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
					Start2, End2, 10.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoreActors, EDrawDebugTrace::ForDuration, Out2, true))
				{
					if(j == 0)
					{
						VaultStartPos = Out2[0].Location;

						DrawDebugSphere(GetWorld(), VaultStartPos, 10.0f, 12,
							FColor::Emerald, false, 10.0f);
					}
					
					VaultMiddlePos = Out2[0].Location;
					CanWarp = true;

					DrawDebugSphere(GetWorld(), VaultStartPos, 10.0f, 12,
						FColor::Yellow, false, 10.0f);

				}
				// 발견되지 않아 착지 지점이 된곳
				else
				{
					TArray<FHitResult> Out3;

					if(UKismetSystemLibrary::LineTraceMulti(GetWorld(), Start2, End2 - FVector(0,0,1000.0f),
						UEngineTypes::ConvertToTraceType(ECC_Visibility),
						false, IgnoreActors, EDrawDebugTrace::ForDuration, Out3, true, FColor::Blue))
					{
						VaultLandPos = Out3[0].Location;
					}

					//DrawDebugLine(GetWorld(), Start2, End2, FColor::Blue, false, 10.0f);
					break;
				}
			}

			break;
		}
	}

	VaultMotionWarp();
	UE_LOG(LogTemp, Warning, TEXT("Start Vault"));
}

void AJHPCharacter::VaultMotionWarp()
{
	float MinRange = GetMesh()->GetComponentLocation().Z - 50.0f;
	float MaxRange = GetMesh()->GetComponentLocation().Z + 50.0f;

	if (CanWarp && VaultLandPos.Z >= MinRange && VaultLandPos.Z <= MaxRange)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		SetActorEnableCollision(false);

		if (MotionWarpingComponent)
		{
			FMotionWarpingTarget WarpingStartTarget;
			WarpingStartTarget.Name = "VaultStart";
			WarpingStartTarget.Location = VaultStartPos;
			WarpingStartTarget.Rotation = GetActorRotation();
			MotionWarpingComponent->AddOrUpdateWarpTarget(WarpingStartTarget);

			FMotionWarpingTarget WarpingMiddleTarget;
			WarpingMiddleTarget.Location = VaultMiddlePos;
			WarpingMiddleTarget.Name = "VaultMiddle";
			WarpingMiddleTarget.Rotation = GetActorRotation(); // 수정
			MotionWarpingComponent->AddOrUpdateWarpTarget(WarpingMiddleTarget);

			FMotionWarpingTarget WarpingLandTarget;
			WarpingLandTarget.Location = VaultLandPos;
			WarpingLandTarget.Name = "VaultLand";
			WarpingLandTarget.Rotation = GetActorRotation(); // 수정
			MotionWarpingComponent->AddOrUpdateWarpTarget(WarpingLandTarget);

			PlayAnimMontage(VaultMontage);

			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUFunction(this, FName("SetMovementMode"));
			GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, VaultMontage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MotionWarpingComponent is not initialized!"));
		}
	}
}

void AJHPCharacter::StateTypeChanged(EStateType PrevType, EStateType InType)
{
	//Super::StateTypeChanged(PrevType, InType);
}
