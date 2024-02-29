// Copyright Epic Games, Inc. All Rights Reserved.

#include "JHPGameMode.h"
#include "JHP/Character/JHPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJHPGameMode::AJHPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/01_Character/BP_Character.BP_Character_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
