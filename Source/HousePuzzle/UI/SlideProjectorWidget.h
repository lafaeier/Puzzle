#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Puzzle/PuzzleTypes.h"
#include "SlideProjectorWidget.generated.h"

class UButton;
class UTextBlock;
class USoundBase;
class ASlideProjector;

UCLASS(Abstract)
class HOUSEPUZZLE_API USlideProjectorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeProjector(ASlideProjector* InProjector);

protected:
	UPROPERTY()
	TObjectPtr<ASlideProjector> Projector;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> OrderDisplayText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> PlayButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> InsertSlideSound;

	TArray<ESlideType> PlayOrder;

	virtual void NativeConstruct() override;

	void AppendSlide(ESlideType SlideType);
	void UpdateOrderDisplay();

	UFUNCTION() void OnSunClicked() { AppendSlide(ESlideType::Sun); }
	UFUNCTION() void OnMoonClicked() { AppendSlide(ESlideType::Moon); }
	UFUNCTION() void OnStarClicked() { AppendSlide(ESlideType::Star); }
	UFUNCTION() void OnCloudClicked() { AppendSlide(ESlideType::Cloud); }

	UFUNCTION()
	void OnPlayClicked();

	UFUNCTION()
	void OnCloseClicked();
};
