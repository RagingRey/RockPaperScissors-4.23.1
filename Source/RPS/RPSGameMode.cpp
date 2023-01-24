// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RPSGameMode.h"
#include "RPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPSGameMode::ARPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
