#include "Puzzle/PuzzlePiecePickup.h"
#include "Puzzle/PuzzleManager.h"
#include "Core/HousePuzzleGameInstance.h"
#include "Engine/GameInstance.h"

APuzzlePiecePickup::APuzzlePiecePickup()
{
	InteractPromptText = FText::FromString(TEXT("Press E to collect piece"));
}

void APuzzlePiecePickup::BeginPlay()
{
	Super::BeginPlay();

	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		if (UPuzzleManager* Manager = GI->GetPuzzleManager())
		{
			if (Manager->IsPieceCollected(PieceIndex))
			{
				bIsCollected = true;
				Destroy();
				return;
			}

			if (Manager->IsPuzzleComplete(LinkedPuzzleId))
			{
				Reveal();
			}
			else if (bHiddenUntilPuzzleComplete)
			{
				HidePickup();
			}

			Manager->OnPuzzleCompleted.AddUObject(this, &APuzzlePiecePickup::OnPuzzleCompleted);
		}
	}
}

void APuzzlePiecePickup::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	if (UPuzzleManager* Manager = GetPuzzleManager())
	{
		Manager->CollectPiece(PieceIndex);
	}

	bIsCollected = true;
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

bool APuzzlePiecePickup::CanInteract(AActor* Interactor) const
{
	if (!Super::CanInteract(Interactor))
	{
		return false;
	}

	if (bIsCollected || !bIsRevealed)
	{
		return false;
	}

	if (const UPuzzleManager* Manager = GetPuzzleManager())
	{
		return !Manager->IsPieceCollected(PieceIndex);
	}

	return true;
}

void APuzzlePiecePickup::Reveal()
{
	bIsRevealed = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	bIsEnabled = true;
}

void APuzzlePiecePickup::HidePickup()
{
	bIsRevealed = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	bIsEnabled = false;
}

void APuzzlePiecePickup::OnPuzzleCompleted(EPuzzleId CompletedId)
{
	if (CompletedId == LinkedPuzzleId)
	{
		Reveal();
	}
}

UPuzzleManager* APuzzlePiecePickup::GetPuzzleManager() const
{
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		return GI->GetPuzzleManager();
	}
	return nullptr;
}
