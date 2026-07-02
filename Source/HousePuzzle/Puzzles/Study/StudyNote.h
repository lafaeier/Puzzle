#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "StudyNote.generated.h"

class UNoteViewerWidget;
class UTexture2D;

UCLASS()
class HOUSEPUZZLE_API AStudyNote : public AInteractableBase
{
	GENERATED_BODY()

public:
	AStudyNote();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<UNoteViewerWidget> NoteWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<UTexture2D> FrontNoteTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<UTexture2D> BackNoteTexture;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	bool bShowingBack = false;

	virtual void OnInteract(AActor* Interactor) override;
};
