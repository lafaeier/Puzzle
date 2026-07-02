#include "Puzzles/Bedroom/BedroomNote.h"
#include "HousePuzzlePlayerController.h"
#include "UI/NoteViewerWidget.h"

ABedroomNote::ABedroomNote()
{
	InteractPromptText = FText::FromString(TEXT("Press E to read note"));
}

void ABedroomNote::OnInteract(AActor* Interactor)
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
			if (NoteWidgetClass)
			{
				if (UNoteViewerWidget* Widget = PC->OpenModalWidget<UNoteViewerWidget>(NoteWidgetClass))
				{
					Widget->ShowNote(NoteTexture);
				}
			}
		}
	}
}
