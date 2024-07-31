#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JHP/Component/StateComponent.h"
#include "CCharacterBase.generated.h"

UCLASS()
class JHP_API ACCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacterBase();
	ACCharacterBase(FString Name);

protected:
	virtual void BeginPlay() override;

	/* Component */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStateComponent> StateComponent;

	/* Getter */
public:
	FORCEINLINE UStateComponent* GetStateComponent() const { return StateComponent; }

protected:
	// State ฐüทร
	virtual void StateTypeChanged(EStateType PrevType, EStateType InType);


	/* field */
public:
	UPROPERTY()
	FString ObjectName;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
