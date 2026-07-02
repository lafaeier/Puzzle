#include "Puzzles/LivingRoom/SlideProjector.h"
#include "Puzzle/PuzzleManager.h"
#include "Puzzle/PuzzlePiecePickup.h"
#include "Core/HousePuzzleGameInstance.h"
#include "HousePuzzlePlayerController.h"
#include "UI/SlideProjectorWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"

ASlideProjector::ASlideProjector()
{
	InteractPromptText = FText::FromString(TEXT("Press E to use projector"));

	CorrectPlayOrder = {
		ESlideType::Sun,
		ESlideType::Cloud,
		ESlideType::Star,
		ESlideType::Moon
	};
}

void ASlideProjector::BeginPlay()
{
	Super::BeginPlay();

	if (!ScreenMeshActor)
	{
		TArray<AActor*> TaggedActors;
		UGameplayStatics::GetAllActorsWithTag(this, FName("ProjectorScreen"), TaggedActors);
		if (TaggedActors.Num() > 0)
		{
			ScreenMeshActor = TaggedActors[0];
		}
	}
}

void ASlideProjector::InsertSlide(ESlideType Type)
{
	if (ProjectorState == ESlideProjectorState::Completed)
	{
		return;
	}

	CollectedSlides.Add(Type);
	UpdateProjectorState();
}

bool ASlideProjector::HasAllSlides() const
{
	return CollectedSlides.Num() >= 4;
}

void ASlideProjector::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	if (!bRequireSorting && HasAllSlides())
	{
		PlaySuccessSequence();
		return;
	}

	if (ProjectorState != ESlideProjectorState::ReadyToPlay)
	{
		return;
	}

	if (APawn* Pawn = Cast<APawn>(Interactor))
	{
		if (AHousePuzzlePlayerController* PC = Cast<AHousePuzzlePlayerController>(Pawn->GetController()))
		{
			if (ProjectorWidgetClass)
			{
				if (USlideProjectorWidget* Widget = PC->OpenModalWidget<USlideProjectorWidget>(ProjectorWidgetClass))
				{
					Widget->InitializeProjector(this);
				}
			}
		}
	}
}

bool ASlideProjector::CanInteract(AActor* Interactor) const
{
	if (!Super::CanInteract(Interactor))
	{
		return false;
	}

	if (ProjectorState == ESlideProjectorState::Completed)
	{
		return false;
	}

	if (!bRequireSorting && HasAllSlides())
	{
		return true;
	}

	return ProjectorState == ESlideProjectorState::ReadyToPlay;
}

bool ASlideProjector::ValidateAndPlay(const TArray<ESlideType>& PlayOrder)
{
	if (ProjectorState != ESlideProjectorState::ReadyToPlay)
	{
		return false;
	}

	ProjectorState = ESlideProjectorState::Playing;

	if (IsPlayOrderCorrect(PlayOrder))
	{
		PlaySuccessSequence();
		return true;
	}

	ProjectorState = ESlideProjectorState::ReadyToPlay;

	if (PlayFailSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PlayFailSound, GetActorLocation());
	}

	return false;
}

void ASlideProjector::UpdateProjectorState()
{
	if (ProjectorState == ESlideProjectorState::Completed)
	{
		return;
	}

	if (HasAllSlides())
	{
		if (bRequireSorting)
		{
			ProjectorState = ESlideProjectorState::ReadyToPlay;
		}
		else
		{
			PlaySuccessSequence();
		}
	}
	else
	{
		ProjectorState = ESlideProjectorState::Collecting;
	}
}

void ASlideProjector::ApplyScreenSuccessMaterial()
{
	if (!ScreenSuccessMaterial)
	{
		return;
	}

	AActor* ScreenActor = ScreenMeshActor;
	if (!ScreenActor)
	{
		TArray<AActor*> TaggedActors;
		UGameplayStatics::GetAllActorsWithTag(this, FName("ProjectorScreen"), TaggedActors);
		if (TaggedActors.Num() > 0)
		{
			ScreenActor = TaggedActors[0];
		}
	}

	if (!ScreenActor)
	{
		return;
	}

	if (UStaticMeshComponent* ScreenMesh = ScreenActor->FindComponentByClass<UStaticMeshComponent>())
	{
		ScreenMesh->SetMaterial(0, ScreenSuccessMaterial);
	}
}

void ASlideProjector::PlaySuccessSequence()
{
	ProjectorState = ESlideProjectorState::Completed;

	ApplyScreenSuccessMaterial();

	if (PlaySuccessSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PlaySuccessSound, GetActorLocation());
	}

	if (UPuzzleManager* Manager = GetPuzzleManager())
	{
		Manager->CompletePuzzle(EPuzzleId::LivingRoom);
	}

	if (LinkedPiece)
	{
		LinkedPiece->Reveal();
	}
}

UPuzzleManager* ASlideProjector::GetPuzzleManager() const
{
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		return GI->GetPuzzleManager();
	}
	return nullptr;
}

bool ASlideProjector::IsPlayOrderCorrect(const TArray<ESlideType>& PlayOrder) const
{
	if (PlayOrder.Num() != CorrectPlayOrder.Num())
	{
		return false;
	}

	for (int32 Index = 0; Index < CorrectPlayOrder.Num(); ++Index)
	{
		if (PlayOrder[Index] != CorrectPlayOrder[Index])
		{
			return false;
		}
	}

	return true;
}
