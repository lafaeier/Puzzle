#include "Puzzles/Study/BookPull.h"
#include "Puzzles/Study/ShelfPuzzleController.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "UObject/UObjectBaseUtility.h"

ABookPull::ABookPull()
{
	InteractPromptText = FText::FromString(TEXT("Press E to pull book"));
}

void ABookPull::BeginPlay()
{
	Super::BeginPlay();
	InitialRelativeLocation = GetRootComponent()->GetRelativeLocation();
	PulledRelativeLocation = InitialRelativeLocation + FVector(0.f, PullDistance, 0.f);

	ResolvePuzzleControllerIfNeeded();

	FString SymbolName = TEXT("None");
	if (const UEnum* SymbolEnum = StaticEnum<EBookSymbol>())
	{
		SymbolName = SymbolEnum->GetNameStringByValue(static_cast<int64>(BookSymbol));
	}

	UE_LOG(LogTemp, Log, TEXT("BookPull '%s': BookSymbol=%s, PuzzleController=%s"),
		*GetName(),
		*SymbolName,
		PuzzleController ? *PuzzleController->GetName() : TEXT("None"));
}

void ABookPull::ResolvePuzzleControllerIfNeeded()
{
	if (IsValid(PuzzleController)
		&& !PuzzleController->HasAnyFlags(RF_ClassDefaultObject)
		&& PuzzleController->GetWorld() == GetWorld())
	{
		return;
	}

	AShelfPuzzleController* ResolvedController = nullptr;
	for (TActorIterator<AShelfPuzzleController> It(GetWorld()); It; ++It)
	{
		AShelfPuzzleController* Candidate = *It;
		if (!IsValid(Candidate))
		{
			continue;
		}

		if (ResolvedController)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("BookPull '%s': multiple ShelfPuzzleControllers found; using '%s'."),
				*GetName(),
				*Candidate->GetName());
		}

		ResolvedController = Candidate;
	}

	if (!ResolvedController)
	{
		UE_LOG(LogTemp, Error, TEXT("BookPull '%s': no ShelfPuzzleController found in level."), *GetName());
		return;
	}

	if (PuzzleController != ResolvedController)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("BookPull '%s': PuzzleController was '%s' (CDO or invalid); auto-resolved to '%s'."),
			*GetName(),
			PuzzleController ? *PuzzleController->GetName() : TEXT("None"),
			*ResolvedController->GetName());
	}

	PuzzleController = ResolvedController;
}

void ABookPull::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	if (PuzzleController)
	{
		PuzzleController->OnBookPulled(BookSymbol, this);
	}
}

bool ABookPull::CanInteract(AActor* Interactor) const
{
	return Super::CanInteract(Interactor) && !bIsPulledOut;
}

void ABookPull::PullOut()
{
	bIsPulledOut = true;
	bIsEnabled = false;
	GetRootComponent()->SetRelativeLocation(PulledRelativeLocation);

	if (PullSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PullSound, GetActorLocation());
	}
}

void ABookPull::SnapBack()
{
	GetRootComponent()->SetRelativeLocation(InitialRelativeLocation);

	if (SnapBackSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SnapBackSound, GetActorLocation());
	}
}
