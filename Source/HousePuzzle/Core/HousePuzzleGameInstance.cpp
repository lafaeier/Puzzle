#include "Core/HousePuzzleGameInstance.h"
#include "Puzzle/PuzzleManager.h"

UPuzzleManager* UHousePuzzleGameInstance::GetPuzzleManager() const
{
	return GetSubsystem<UPuzzleManager>();
}
