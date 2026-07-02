#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "Puzzle/PuzzleTypes.h"
#include "SlideProjector.generated.h"

class USlideProjectorWidget;
class APuzzlePiecePickup;
class UPuzzleManager;
class USoundBase;
class UMaterialInterface;

UCLASS()
class HOUSEPUZZLE_API ASlideProjector : public AInteractableBase
{
	GENERATED_BODY()

public:
	ASlideProjector();

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	TSet<ESlideType> CollectedSlides;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<ESlideType> CorrectPlayOrder;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	ESlideProjectorState ProjectorState = ESlideProjectorState::Collecting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<APuzzlePiecePickup> LinkedPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	bool bRequireSorting = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<USlideProjectorWidget> ProjectorWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> PlaySuccessSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> PlayFailSound;

	/** Level-placed screen mesh; falls back to actor tagged ProjectorScreen if unset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<AActor> ScreenMeshActor;

	/** Applied to screen mesh slot 0 on successful playback (e.g. MI_Projector_Screen_Composite). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<UMaterialInterface> ScreenSuccessMaterial;

	void InsertSlide(ESlideType Type);
	bool HasAllSlides() const;

	virtual void OnInteract(AActor* Interactor) override;
	virtual bool CanInteract(AActor* Interactor) const override;

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	bool ValidateAndPlay(const TArray<ESlideType>& PlayOrder);

protected:
	virtual void BeginPlay() override;

	void UpdateProjectorState();
	void PlaySuccessSequence();
	void ApplyScreenSuccessMaterial();
	UPuzzleManager* GetPuzzleManager() const;
	bool IsPlayOrderCorrect(const TArray<ESlideType>& PlayOrder) const;
};
