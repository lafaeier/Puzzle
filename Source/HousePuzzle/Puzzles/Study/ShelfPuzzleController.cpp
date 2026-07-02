#include "Puzzles/Study/ShelfPuzzleController.h"
#include "Puzzles/Study/BookPull.h"
#include "Puzzle/PuzzleManager.h"
#include "Puzzle/PuzzlePiecePickup.h"
#include "Core/HousePuzzleGameInstance.h"
#include "EngineUtils.h"
#include "UObject/UObjectBaseUtility.h"

namespace
{
	FString BookSymbolToString(EBookSymbol Symbol)
	{
		if (const UEnum* SymbolEnum = StaticEnum<EBookSymbol>())
		{
			return SymbolEnum->GetNameStringByValue(static_cast<int64>(Symbol));
		}

		return TEXT("Unknown");
	}

	bool IsRuntimeActorReference(const AActor* Actor, const UWorld* World)
	{
		return IsValid(Actor)
			&& !Actor->HasAnyFlags(RF_ClassDefaultObject)
			&& Actor->GetWorld() == World;
	}
}

const TArray<EBookSymbol>& AShelfPuzzleController::GetDefaultCorrectOrder()
{
	static const TArray<EBookSymbol> DefaultOrder = {
		EBookSymbol::Circle,
		EBookSymbol::TriangleUp,
		EBookSymbol::TriangleDown,
		EBookSymbol::FilledDiamond,
		EBookSymbol::Diamond
	};

	return DefaultOrder;
}

AShelfPuzzleController::AShelfPuzzleController()
{
	PrimaryActorTick.bCanEverTick = false;
	CorrectOrder = GetDefaultCorrectOrder();
}

void AShelfPuzzleController::BeginPlay()
{
	Super::BeginPlay();

	EnsureDefaultCorrectOrder();
	ResolveLinkedPieceIfNeeded();

	UE_LOG(LogTemp, Log, TEXT("ShelfPuzzleController '%s': CorrectOrder=%d entries, CurrentStep=%d, LinkedPiece=%s"),
		*GetName(),
		CorrectOrder.Num(),
		CurrentStep,
		LinkedPiece ? *LinkedPiece->GetName() : TEXT("None"));
}

void AShelfPuzzleController::EnsureDefaultCorrectOrder()
{
	const TArray<EBookSymbol>& DefaultOrder = GetDefaultCorrectOrder();
	bool bNeedsReset = CorrectOrder.Num() != DefaultOrder.Num();
	if (!bNeedsReset)
	{
		for (int32 Index = 0; Index < DefaultOrder.Num(); ++Index)
		{
			if (CorrectOrder[Index] != DefaultOrder[Index])
			{
				bNeedsReset = true;
				break;
			}
		}
	}

	if (!bNeedsReset)
	{
		return;
	}

	UE_LOG(LogTemp, Warning,
		TEXT("ShelfPuzzleController '%s': CorrectOrder invalid (%d entries). Resetting to default 5-step sequence."),
		*GetName(),
		CorrectOrder.Num());

	CorrectOrder = DefaultOrder;
}

void AShelfPuzzleController::ResolveLinkedPieceIfNeeded()
{
	if (IsRuntimeActorReference(LinkedPiece, GetWorld()))
	{
		return;
	}

	for (TActorIterator<APuzzlePiecePickup> It(GetWorld()); It; ++It)
	{
		APuzzlePiecePickup* Candidate = *It;
		if (!IsValid(Candidate) || Candidate->LinkedPuzzleId != EPuzzleId::Study)
		{
			continue;
		}

		LinkedPiece = Candidate;
		UE_LOG(LogTemp, Warning,
			TEXT("ShelfPuzzleController '%s': LinkedPiece was not a level instance; auto-resolved to '%s'."),
			*GetName(),
			*Candidate->GetName());
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("ShelfPuzzleController '%s': no Study puzzle piece found in level."), *GetName());
}

void AShelfPuzzleController::OnBookPulled(EBookSymbol Symbol, ABookPull* Book)
{
	if (PuzzleState == EShelfPuzzleState::Completed || !Book)
	{
		return;
	}

	if (Symbol == EBookSymbol::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShelfPuzzle: '%s' has BookSymbol=None (decoy or unset). Set BookSymbol on the book BP instance."),
			*GetNameSafe(Book));
		Book->SnapBack();
		return;
	}

	if (!CorrectOrder.IsValidIndex(CurrentStep))
	{
		UE_LOG(LogTemp, Error,
			TEXT("ShelfPuzzleController '%s': CurrentStep=%d out of range for CorrectOrder (%d entries)."),
			*GetName(),
			CurrentStep,
			CorrectOrder.Num());
		return;
	}

	const EBookSymbol ExpectedSymbol = CorrectOrder[CurrentStep];
	if (Symbol == ExpectedSymbol)
	{
		UE_LOG(LogTemp, Log, TEXT("ShelfPuzzle [%s]: step %d/%d OK — pulled %s"),
			*GetName(), CurrentStep + 1, CorrectOrder.Num(), *BookSymbolToString(Symbol));
		Book->PullOut();
		++CurrentStep;

		if (CurrentStep >= CorrectOrder.Num())
		{
			CompletePuzzle();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning,
			TEXT("ShelfPuzzle [%s]: step %d/%d FAIL — pulled %s, expected %s (book: %s). ControllerIsCDO=%d"),
			*GetName(),
			CurrentStep + 1,
			CorrectOrder.Num(),
			*BookSymbolToString(Symbol),
			*BookSymbolToString(ExpectedSymbol),
			*GetNameSafe(Book),
			HasAnyFlags(RF_ClassDefaultObject));
		Book->SnapBack();
	}
}

void AShelfPuzzleController::CompletePuzzle()
{
	PuzzleState = EShelfPuzzleState::Completed;

	if (SecretCompartmentActor)
	{
		SecretCompartmentActor->SetActorHiddenInGame(false);
		SecretCompartmentActor->SetActorEnableCollision(true);
	}

	if (UPuzzleManager* Manager = GetPuzzleManager())
	{
		Manager->CompletePuzzle(EPuzzleId::Study);
	}

	if (LinkedPiece)
	{
		LinkedPiece->Reveal();
	}
}

UPuzzleManager* AShelfPuzzleController::GetPuzzleManager() const
{
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		return GI->GetPuzzleManager();
	}
	return nullptr;
}
