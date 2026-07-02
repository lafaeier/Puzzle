#include "Puzzles/Bedroom/BedroomLockbox.h"
#include "Puzzle/PuzzleManager.h"
#include "Puzzle/PuzzlePiecePickup.h"
#include "Core/HousePuzzleGameInstance.h"
#include "HousePuzzlePlayerController.h"
#include "UI/LockboxWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ABedroomLockbox::ABedroomLockbox()
{
	InteractPromptText = FText::FromString(TEXT("Press E to examine lockbox"));
}

void ABedroomLockbox::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	if (LockboxState != ELockboxState::Locked)
	{
		return;
	}

	if (APawn* Pawn = Cast<APawn>(Interactor))
	{
		if (AHousePuzzlePlayerController* PC = Cast<AHousePuzzlePlayerController>(Pawn->GetController()))
		{
			if (LockboxWidgetClass)
			{
				if (ULockboxWidget* Widget = PC->OpenModalWidget<ULockboxWidget>(LockboxWidgetClass))
				{
					Widget->InitializeLockbox(this);
				}
			}
		}
	}
}

bool ABedroomLockbox::CanInteract(AActor* Interactor) const
{
	if (!Super::CanInteract(Interactor))
	{
		return false;
	}

	return LockboxState != ELockboxState::Open;
}

void ABedroomLockbox::SubmitCode(const FString& Code)
{
	if (LockboxState != ELockboxState::Locked)
	{
		return;
	}

	if (Code.Equals(CorrectCode))
	{
		OpenLockbox();
	}
	else
	{
		PlayRejectFeedback();
	}
}

void ABedroomLockbox::OpenLockbox()
{
	LockboxState = ELockboxState::Open;

	if (OpenSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
	}

	if (UPuzzleManager* Manager = GetPuzzleManager())
	{
		Manager->CompletePuzzle(EPuzzleId::Bedroom);
	}

	if (LinkedPiece)
	{
		LinkedPiece->Reveal();
	}
}

void ABedroomLockbox::PlayRejectFeedback()
{
	LockboxState = ELockboxState::Shaking;

	if (RejectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, RejectSound, GetActorLocation());
	}

	const FVector OriginalLocation = GetActorLocation();
	const FVector ShakeOffset(0.f, FMath::RandRange(-2.f, 2.f), 0.f);
	SetActorLocation(OriginalLocation + ShakeOffset);

	GetWorldTimerManager().SetTimer(ShakeTimerHandle, this, &ABedroomLockbox::EndShake, 0.3f, false);
}

void ABedroomLockbox::EndShake()
{
	LockboxState = ELockboxState::Locked;
}

UPuzzleManager* ABedroomLockbox::GetPuzzleManager() const
{
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		return GI->GetPuzzleManager();
	}
	return nullptr;
}
