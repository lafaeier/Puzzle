#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "Puzzle/PuzzleTypes.h"
#include "SlideItem.generated.h"

class ASlideProjector;

UCLASS()
class HOUSEPUZZLE_API ASlideItem : public AInteractableBase
{
	GENERATED_BODY()

public:
	ASlideItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	ESlideType SlideType = ESlideType::Sun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<ASlideProjector> Projector;

	virtual void OnInteract(AActor* Interactor) override;
	virtual bool CanInteract(AActor* Interactor) const override;

protected:
	UPROPERTY()
	bool bIsCollected = false;
};
