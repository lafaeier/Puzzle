#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteViewerWidget.generated.h"

class UImage;
class UButton;
class UTexture2D;

UCLASS(Abstract)
class HOUSEPUZZLE_API UNoteViewerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowNote(UTexture2D* NoteTexture);

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> NoteImage;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> CloseButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCloseClicked();
};
