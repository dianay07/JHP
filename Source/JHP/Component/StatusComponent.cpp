#include "StatusComponent.h"

#include "JHP/Character/JHPCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "JHP/UI/CWB_HUD.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AJHPCharacter>(GetOwner());
}


void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UStatusComponent::Damage(float InValue)
{
	if(Health > 0.0f)
	{
		Health = Health - InValue;

		Owner->GetHUD()->HealthBar->SetPercent(Health / MaxHealth);
		Owner->GetHUD()->TextBlock->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Health)));

		if (Health <= 0)
			return true;
		else
			return false;
	}
	else
	{
		return true;
	}
}

void UStatusComponent::IncreaseMaxHealth(float InValue)
{
	MaxHealth = MaxHealth + InValue;
	Health = MaxHealth;

	Owner->GetHUD()->HealthBar->SetPercent(MaxHealth);
	Owner->GetHUD()->TextBlock->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Health)));
}

void UStatusComponent::IncreaseHealth(float InValue)
{
	Health = Health + InValue;

	if (Health > MaxHealth)
		Health = MaxHealth;

	Owner->GetHUD()->HealthBar->SetPercent(Health / MaxHealth);
	Owner->GetHUD()->TextBlock->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Health)));
}

bool UStatusComponent::UseStamina(float InValue)
{
	if(Stamina > 0.0f)
	{
		Stamina = Stamina - InValue;

		Owner->GetHUD()->StaminaBar->SetPercent(Stamina / MaxStamina);

		if (Stamina <= 0)
			return true;
		else
			return false;
	}
	else
	{
		return true;
	}
}

void UStatusComponent::IncreaseMaxStamina(float InValue)
{
	MaxStamina = MaxStamina + InValue;
	Stamina = MaxStamina;

	Owner->GetHUD()->StaminaBar->SetPercent(MaxStamina);
}

void UStatusComponent::IncreaseStamina(float InValue)
{
	Stamina = Stamina + InValue;

	if(Stamina > MaxStamina)
		Stamina = MaxStamina;

	Owner->GetHUD()->StaminaBar->SetPercent(Stamina / MaxStamina);
}

