#include "Puzzles/LivingRoom/PuzzleBoardTrigger.h"
#include "Puzzle/PuzzleManager.h"
#include "Core/HousePuzzleGameInstance.h"
#include "HousePuzzlePlayerController.h"
#include "UI/PuzzleBoardWidget.h"

APuzzleBoardTrigger::APuzzleBoardTrigger()
{
	InteractPromptText = FText::FromString(TEXT("Press E to assemble puzzle"));
}

void APuzzleBoardTrigger::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	if (APawn* Pawn = Cast<APawn>(Interactor))
	{
		if (AHousePuzzlePlayerController* PC = Cast<AHousePuzzlePlayerController>(Pawn->GetController()))
		{
			if (PuzzleBoardWidgetClass)
			{
				PC->OpenModalWidget<UPuzzleBoardWidget>(PuzzleBoardWidgetClass);
			}
		}
	}
}

bool APuzzleBoardTrigger::CanInteract(AActor* Interactor) const
{
	if (!Super::CanInteract(Interactor))
	{
		return false;
	}

	if (const UPuzzleManager* Manager = GetPuzzleManager())
	{
		return Manager->CanShowPuzzleBoard() && !Manager->IsDoorUnlocked();
	}

	return false;
}

UPuzzleManager* APuzzleBoardTrigger::GetPuzzleManager() const
{
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		return GI->GetPuzzleManager();
	}
	return nullptr;
}
