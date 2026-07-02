#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "BedroomNote.generated.h"

class UNoteViewerWidget;
class UTexture2D;

UCLASS()
class HOUSEPUZZLE_API ABedroomNote : public AInteractableBase
{
	GENERATED_BODY()

public:
	ABedroomNote();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<UNoteViewerWidget> NoteWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<UTexture2D> NoteTexture;

	virtual void OnInteract(AActor* Interactor) override;
};
