#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


class AJHPCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JHP_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

public:
	UPROPERTY(EditAnywhere, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "EXP")
	float EXP;

	UPROPERTY(EditAnywhere, Category = "EXP")
	float MaxEXP = 100.0f;

	UPROPERTY(EditAnywhere, Category = "EXP")
	int Level = 1;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "JH")
	bool Damage(float InValue);
	void IncreaseMaxHealth(float InValue);

	UFUNCTION(BlueprintCallable, Category = "JH")
	void IncreaseHealth(float InValue);

	bool UseStamina(float InValue);
	void IncreaseMaxStamina(float InValue);
	void IncreaseStamina(float InValue);

private:
	TObjectPtr<AJHPCharacter> Owner;
};
