#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "BedroomPhotoFrame.generated.h"

class UDecalComponent;
class UTimelineComponent;
class UCurveFloat;

UCLASS()
class HOUSEPUZZLE_API ABedroomPhotoFrame : public AInteractableBase
{
	GENERATED_BODY()

public:
	ABedroomPhotoFrame();

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	bool bIsFlipped = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Puzzle")
	TObjectPtr<UDecalComponent> BackDecal;

	virtual void OnInteract(AActor* Interactor) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Puzzle")
	TObjectPtr<UCurveFloat> FlipCurve;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> FlipTimeline;

	FRotator InitialRotation;
	FRotator TargetRotation;

	UFUNCTION()
	void OnFlipTimelineUpdate(float Value);

	UFUNCTION()
	void OnFlipTimelineFinished();
};
