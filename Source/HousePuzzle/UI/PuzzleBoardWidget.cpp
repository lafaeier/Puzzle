#include "UI/PuzzleBoardWidget.h"
#include "Puzzle/PuzzleManager.h"
#include "Core/HousePuzzleGameInstance.h"
#include "HousePuzzlePlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPuzzleBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializePieces();
	UpdateStatusText();

	if (UButton* PieceButton = Cast<UButton>(GetWidgetFromName(TEXT("Piece0Button"))))
	{
		PieceButton->OnClicked.AddDynamic(this, &UPuzzleBoardWidget::OnPiece0Clicked);
	}
	if (UButton* PieceButton = Cast<UButton>(GetWidgetFromName(TEXT("Piece1Button"))))
	{
		PieceButton->OnClicked.AddDynamic(this, &UPuzzleBoardWidget::OnPiece1Clicked);
	}
	if (UButton* PieceButton = Cast<UButton>(GetWidgetFromName(TEXT("Piece2Button"))))
	{
		PieceButton->OnClicked.AddDynamic(this, &UPuzzleBoardWidget::OnPiece2Clicked);
	}
	if (UButton* PieceButton = Cast<UButton>(GetWidgetFromName(TEXT("Piece3Button"))))
	{
		PieceButton->OnClicked.AddDynamic(this, &UPuzzleBoardWidget::OnPiece3Clicked);
	}
	if (UButton* CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton"))))
	{
		CloseButton->OnClicked.AddDynamic(this, &UPuzzleBoardWidget::OnCloseClicked);
	}
}

void UPuzzleBoardWidget::InitializePieces()
{
	Pieces.SetNum(4);

	const TArray<FVector2D> TargetPositions = {
		FVector2D(0.f, 0.f),
		FVector2D(100.f, 0.f),
		FVector2D(0.f, 100.f),
		FVector2D(100.f, 100.f)
	};

	for (int32 Index = 0; Index < 4; ++Index)
	{
		Pieces[Index].PieceIndex = Index;
		Pieces[Index].TargetPosition = TargetPositions[Index];
		Pieces[Index].CurrentPosition = FVector2D(50.f + Index * 120.f, 200.f);
		Pieces[Index].bIsPlaced = false;
	}
}

void UPuzzleBoardWidget::OnPiece0Clicked() { SnapPieceToTarget(0); }
void UPuzzleBoardWidget::OnPiece1Clicked() { SnapPieceToTarget(1); }
void UPuzzleBoardWidget::OnPiece2Clicked() { SnapPieceToTarget(2); }
void UPuzzleBoardWidget::OnPiece3Clicked() { SnapPieceToTarget(3); }

void UPuzzleBoardWidget::SnapPieceToTarget(int32 PieceIndex)
{
	if (!Pieces.IsValidIndex(PieceIndex) || Pieces[PieceIndex].bIsPlaced)
	{
		return;
	}

	Pieces[PieceIndex].CurrentPosition = Pieces[PieceIndex].TargetPosition;
	Pieces[PieceIndex].bIsPlaced = true;
	UpdateStatusText();
	CheckWin();
}

void UPuzzleBoardWidget::UpdateStatusText()
{
	if (!StatusText)
	{
		return;
	}

	int32 PlacedCount = 0;
	for (const FPuzzleBoardPiece& Piece : Pieces)
	{
		if (Piece.bIsPlaced)
		{
			++PlacedCount;
		}
	}

	StatusText->SetText(FText::FromString(FString::Printf(TEXT("Placed %d/4 — click pieces to snap"), PlacedCount)));
}

void UPuzzleBoardWidget::CheckWin()
{
	if (!AreAllPiecesPlaced())
	{
		return;
	}

	CompleteBoard();
}

bool UPuzzleBoardWidget::AreAllPiecesPlaced() const
{
	for (const FPuzzleBoardPiece& Piece : Pieces)
	{
		if (!Piece.bIsPlaced)
		{
			return false;
		}
	}
	return true;
}

void UPuzzleBoardWidget::CompleteBoard()
{
	if (CompleteSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), CompleteSound);
	}

	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		if (UPuzzleManager* Manager = GI->GetPuzzleManager())
		{
			Manager->CompletePuzzleBoard();
		}
	}

	if (StatusText)
	{
		StatusText->SetText(FText::FromString(TEXT("Complete! The door is unlocked.")));
	}
}

void UPuzzleBoardWidget::OnCloseClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AHousePuzzlePlayerController* PuzzlePC = Cast<AHousePuzzlePlayerController>(PC))
		{
			PuzzlePC->CloseModalWidget();
		}
	}
}
