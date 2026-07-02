// Copyright Epic Games, Inc. All Rights Reserved.

#include "HousePuzzleGameMode.h"
#include "HousePuzzleCharacter.h"
#include "HousePuzzlePlayerController.h"

AHousePuzzleGameMode::AHousePuzzleGameMode()
{
	DefaultPawnClass = AHousePuzzleCharacter::StaticClass();
	PlayerControllerClass = AHousePuzzlePlayerController::StaticClass();
}
