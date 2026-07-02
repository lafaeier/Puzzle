#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "Puzzle/PuzzleTypes.h"
#include "BookPull.generated.h"

class AShelfPuzzleController;

UCLASS()
class HOUSEPUZZLE_API ABookPull : public AInteractableBase
{
	GENERATED_BODY()

public:
	ABookPull();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	EBookSymbol BookSymbol = EBookSymbol::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<AShelfPuzzleController> PuzzleController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	float PullDistance = 15.f;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	bool bIsPulledOut = false;

	virtual void OnInteract(AActor* Interactor) override;
	virtual bool CanInteract(AActor* Interactor) const override;

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void PullOut();

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void SnapBack();

protected:
	FVector InitialRelativeLocation;
	FVector PulledRelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> PullSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> SnapBackSound;

	virtual void BeginPlay() override;

	void ResolvePuzzleControllerIfNeeded();
};
