#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWB_HUD.generated.h"

UCLASS()
class JHP_API UCWB_HUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* StaminaBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock;
};
