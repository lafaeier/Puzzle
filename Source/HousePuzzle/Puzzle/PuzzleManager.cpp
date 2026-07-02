#include "Puzzle/PuzzleManager.h"
#include "HousePuzzle.h"

void UPuzzleManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CompletedPuzzles.Empty();
	CollectedPieceIndices.Empty();
	bPuzzleBoardCompleted = false;
	bDoorUnlocked = false;
}

bool UPuzzleManager::IsPuzzleComplete(EPuzzleId Id) const
{
	return CompletedPuzzles.Contains(Id);
}

void UPuzzleManager::CompletePuzzle(EPuzzleId Id)
{
	if (CompletedPuzzles.Contains(Id))
	{
		return;
	}

	CompletedPuzzles.Add(Id);
	OnPuzzleCompleted.Broadcast(Id);
	UE_LOG(LogHousePuzzle, Log, TEXT("Puzzle completed: %d"), static_cast<int32>(Id));
}

bool UPuzzleManager::IsPieceCollected(int32 PieceIndex) const
{
	return CollectedPieceIndices.Contains(PieceIndex);
}

int32 UPuzzleManager::GetCollectedPieceCount() const
{
	return CollectedPieceIndices.Num();
}

void UPuzzleManager::CollectPiece(int32 PieceIndex)
{
	if (PieceIndex < 0 || PieceIndex >= static_cast<int32>(EPuzzleId::COUNT))
	{
		return;
	}

	if (CollectedPieceIndices.Contains(PieceIndex))
	{
		return;
	}

	CollectedPieceIndices.Add(PieceIndex);
	OnPieceCollected.Broadcast(PieceIndex);
	UE_LOG(LogHousePuzzle, Log, TEXT("Piece collected: %d (total %d)"), PieceIndex, CollectedPieceIndices.Num());
}

bool UPuzzleManager::CanShowPuzzleBoard() const
{
	return GetCollectedPieceCount() >= static_cast<int32>(EPuzzleId::COUNT);
}

void UPuzzleManager::CompletePuzzleBoard()
{
	if (bPuzzleBoardCompleted)
	{
		return;
	}

	bPuzzleBoardCompleted = true;
	bDoorUnlocked = true;
	OnPuzzleBoardCompleted.Broadcast();
	UE_LOG(LogHousePuzzle, Log, TEXT("Puzzle board completed — door unlocked"));
}

bool UPuzzleManager::IsDoorUnlocked() const
{
	return bDoorUnlocked;
}

EPuzzleId UPuzzleManager::PieceIndexToPuzzleId(int32 PieceIndex)
{
	switch (PieceIndex)
	{
	case 0: return EPuzzleId::Bedroom;
	case 1: return EPuzzleId::Balcony;
	case 2: return EPuzzleId::LivingRoom;
	case 3: return EPuzzleId::Study;
	default: return EPuzzleId::Bedroom;
	}
}

int32 UPuzzleManager::PuzzleIdToPieceIndex(EPuzzleId Id)
{
	switch (Id)
	{
	case EPuzzleId::Bedroom: return 0;
	case EPuzzleId::Balcony: return 1;
	case EPuzzleId::LivingRoom: return 2;
	case EPuzzleId::Study: return 3;
	default: return 0;
	}
}
