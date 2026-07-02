#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "PuzzleBoardTrigger.generated.h"

class UPuzzleBoardWidget;
class UPuzzleManager;

UCLASS()
class HOUSEPUZZLE_API APuzzleBoardTrigger : public AInteractableBase
{
	GENERATED_BODY()

public:
	APuzzleBoardTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<UPuzzleBoardWidget> PuzzleBoardWidgetClass;

	virtual void OnInteract(AActor* Interactor) override;
	virtual bool CanInteract(AActor* Interactor) const override;

protected:
	UPuzzleManager* GetPuzzleManager() const;
};
