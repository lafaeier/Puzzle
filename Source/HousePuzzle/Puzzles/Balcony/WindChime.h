#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "Puzzle/PuzzleTypes.h"
#include "WindChime.generated.h"

class ABalconyPuzzleController;
class UPointLightComponent;

UCLASS()
class HOUSEPUZZLE_API AWindChime : public AInteractableBase
{
	GENERATED_BODY()

public:
	AWindChime();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	EChimeColor ChimeColor = EChimeColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<ABalconyPuzzleController> PuzzleController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float PitchMultiplier = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Puzzle")
	TObjectPtr<UPointLightComponent> HighlightLight;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	bool bIsActivated = false;

	virtual void OnInteract(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void ActivateChime();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> ChimeSound;
};
