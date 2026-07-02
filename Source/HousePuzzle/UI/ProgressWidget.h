#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressWidget.generated.h"

class UTextBlock;

UCLASS(Abstract)
class HOUSEPUZZLE_API UProgressWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateProgress(int32 Collected, int32 Total);

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ProgressTextBlock;
};
