#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Puzzle/PuzzleTypes.h"
#include "PuzzleManager.generated.h"

UCLASS()
class HOUSEPUZZLE_API UPuzzleManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	bool IsPuzzleComplete(EPuzzleId Id) const;
	void CompletePuzzle(EPuzzleId Id);

	bool IsPieceCollected(int32 PieceIndex) const;
	int32 GetCollectedPieceCount() const;
	void CollectPiece(int32 PieceIndex);

	bool CanShowPuzzleBoard() const;
	void CompletePuzzleBoard();
	bool IsDoorUnlocked() const;

	static EPuzzleId PieceIndexToPuzzleId(int32 PieceIndex);
	static int32 PuzzleIdToPieceIndex(EPuzzleId Id);

	FOnPuzzleCompleted OnPuzzleCompleted;
	FOnPieceCollected OnPieceCollected;
	FOnPuzzleBoardCompleted OnPuzzleBoardCompleted;

private:
	UPROPERTY()
	TSet<EPuzzleId> CompletedPuzzles;

	UPROPERTY()
	TSet<int32> CollectedPieceIndices;

	UPROPERTY()
	bool bPuzzleBoardCompleted = false;

	UPROPERTY()
	bool bDoorUnlocked = false;
};
