#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "Puzzle/PuzzleTypes.h"
#include "PuzzlePiecePickup.generated.h"

class UPuzzleManager;

UCLASS()
class HOUSEPUZZLE_API APuzzlePiecePickup : public AInteractableBase
{
	GENERATED_BODY()

public:
	APuzzlePiecePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	int32 PieceIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	EPuzzleId LinkedPuzzleId = EPuzzleId::Bedroom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	bool bHiddenUntilPuzzleComplete = true;

	virtual void OnInteract(AActor* Interactor) override;
	virtual bool CanInteract(AActor* Interactor) const override;

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void Reveal();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bIsCollected = false;

	UPROPERTY()
	bool bIsRevealed = false;

	void HidePickup();
	void OnPuzzleCompleted(EPuzzleId CompletedId);
	UPuzzleManager* GetPuzzleManager() const;
};
