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
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "JHP/Equipment/Equipment.h"

//////////////////////////////////////////////////////////////////////////
// AJHPCharacter

AJHPCharacter::AJHPCharacter()
{
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
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("State Component"));
	JobComponent = CreateDefaultSubobject<UJobComponent>(TEXT("Job Component"));
	EquipComponent = CreateDefaultSubobject<UEquipComponent>(TEXT("Equip Component"));

	/* AnimInstance */
	TSubclassOf<UAnimInstance> instance = ConstructorHelpers::FClassFinder<UAnimInstance>(TEXT("/Script/Engine.AnimBlueprint'/Game/01_Character/ABP_Character.ABP_Character_C'")).Class;
	if(instance != nullptr)
	{
		GetMesh()->SetAnimClass(instance);
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

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	JobComponent->ChangeJob(EJob::Warrior);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJHPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJHPCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJHPCharacter::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AJHPCharacter::Attack);

		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Ongoing, this, &AJHPCharacter::StartGuard);
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Completed, this, &AJHPCharacter::StopGuard);

		// 키 변경 코드 : InputAction 의 키가 그대로 바뀜
		DefaultMappingContext->UnmapAllKeysFromAction(AttackAction);
		DefaultMappingContext->MapKey(AttackAction, EKeys::T);
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
	StateComponent->SetStateGuard();
}

void AJHPCharacter::StopGuard()
{
}

void AJHPCharacter::StateTypeChanged(EStateType PrevType, EStateType InType)
{
	//switch (EStateType)
	//{
	//case EStateType::Guard :
		// TODO : 가드 중 실행할 함수
	//	break;
	//}
}
