#include "UI/NoteViewerWidget.h"
#include "HousePuzzlePlayerController.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UNoteViewerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UNoteViewerWidget::OnCloseClicked);
	}
}

void UNoteViewerWidget::ShowNote(UTexture2D* NoteTexture)
{
	if (NoteImage && NoteTexture)
	{
		NoteImage->SetBrushFromTexture(NoteTexture);
	}
}

void UNoteViewerWidget::OnCloseClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AHousePuzzlePlayerController* PuzzlePC = Cast<AHousePuzzlePlayerController>(PC))
		{
			PuzzlePC->CloseModalWidget();
		}
	}
}
