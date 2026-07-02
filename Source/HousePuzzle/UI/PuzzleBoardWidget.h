#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Puzzle/PuzzleTypes.h"
#include "PuzzleBoardWidget.generated.h"

class UButton;
class UTextBlock;
class USoundBase;

UCLASS(Abstract)
class HOUSEPUZZLE_API UPuzzleBoardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CheckWin();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Puzzle")
	float SnapThreshold = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> CompleteSound;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StatusText;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	TArray<FPuzzleBoardPiece> Pieces;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPiece0Clicked();

	UFUNCTION()
	void OnPiece1Clicked();

	UFUNCTION()
	void OnPiece2Clicked();

	UFUNCTION()
	void OnPiece3Clicked();

	UFUNCTION()
	void OnCloseClicked();

	void InitializePieces();
	void SnapPieceToTarget(int32 PieceIndex);
	void UpdateStatusText();
	bool AreAllPiecesPlaced() const;
	void CompleteBoard();
};
