#include "Puzzles/Study/StudyNote.h"
#include "HousePuzzlePlayerController.h"
#include "UI/NoteViewerWidget.h"

AStudyNote::AStudyNote()
{
	InteractPromptText = FText::FromString(TEXT("Press E to read note"));
}

void AStudyNote::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	bShowingBack = !bShowingBack;
	const UTexture2D* TextureToShow = bShowingBack ? BackNoteTexture.Get() : FrontNoteTexture.Get();

	if (APawn* Pawn = Cast<APawn>(Interactor))
	{
		if (AHousePuzzlePlayerController* PC = Cast<AHousePuzzlePlayerController>(Pawn->GetController()))
		{
			if (NoteWidgetClass)
			{
				if (UNoteViewerWidget* Widget = PC->OpenModalWidget<UNoteViewerWidget>(NoteWidgetClass))
				{
					Widget->ShowNote(const_cast<UTexture2D*>(TextureToShow));
				}
			}
		}
	}
}
