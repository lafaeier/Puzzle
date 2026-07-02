#include "Puzzles/Balcony/BalconyPuzzleController.h"
#include "Puzzles/Balcony/WindChime.h"
#include "Puzzle/PuzzleManager.h"
#include "Puzzle/PuzzlePiecePickup.h"
#include "Core/HousePuzzleGameInstance.h"
#include "Kismet/GameplayStatics.h"

ABalconyPuzzleController::ABalconyPuzzleController()
{
	PrimaryActorTick.bCanEverTick = false;

	CorrectSequence = {
		EChimeColor::Blue,
		EChimeColor::Red,
		EChimeColor::Green,
		EChimeColor::Yellow,
		EChimeColor::Purple
	};
}

void ABalconyPuzzleController::BeginPlay()
{
	Super::BeginPlay();

	if (FlowerPotActor)
	{
		FlowerPotInitialLocation = FlowerPotActor->GetActorLocation();
	}
}

void ABalconyPuzzleController::OnChimeClicked(EChimeColor Color, AWindChime* Chime)
{
	if (PuzzleState == EBalconyPuzzleState::Completed || !CorrectSequence.IsValidIndex(CurrentIndex))
	{
		return;
	}

	if (Color == CorrectSequence[CurrentIndex])
	{
		HandleCorrectChime(Chime);
	}
	else
	{
		HandleWrongChime();
	}
}

void ABalconyPuzzleController::HandleCorrectChime(AWindChime* Chime)
{
	if (Chime)
	{
		Chime->ActivateChime();
	}

	++CurrentIndex;

	if (CurrentIndex >= CorrectSequence.Num())
	{
		CompletePuzzle();
	}
}

void ABalconyPuzzleController::HandleWrongChime()
{
	if (WrongChimeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, WrongChimeSound, GetActorLocation());
	}
}

void ABalconyPuzzleController::CompletePuzzle()
{
	PuzzleState = EBalconyPuzzleState::Completed;

	if (UPuzzleManager* Manager = GetPuzzleManager())
	{
		Manager->CompletePuzzle(EPuzzleId::Balcony);
	}

	MoveFlowerPot();

	if (LinkedPiece)
	{
		LinkedPiece->Reveal();
	}
}

void ABalconyPuzzleController::MoveFlowerPot()
{
	if (!FlowerPotActor || bFlowerPotMoved)
	{
		return;
	}

	if (FlowerPotInitialLocation.IsNearlyZero())
	{
		FlowerPotInitialLocation = FlowerPotActor->GetActorLocation();
	}

	FlowerPotActor->SetActorLocation(FlowerPotInitialLocation + FlowerPotHiddenOffset);
	bFlowerPotMoved = true;

	if (FlowerPotMoveSound)
	{
		const FVector SoundLocation = FlowerPotActor->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, FlowerPotMoveSound, SoundLocation);
	}
}

UPuzzleManager* ABalconyPuzzleController::GetPuzzleManager() const
{
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		return GI->GetPuzzleManager();
	}
	return nullptr;
}
