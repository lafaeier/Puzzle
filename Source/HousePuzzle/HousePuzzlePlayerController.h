// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "HousePuzzlePlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class UProgressWidget;
class UInteractPromptWidget;

UCLASS(config="Game")
class HOUSEPUZZLE_API AHousePuzzlePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHousePuzzlePlayerController();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UProgressWidget> ProgressWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInteractPromptWidget> InteractPromptWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> ActiveModalWidget;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UProgressWidget> ProgressWidget;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UInteractPromptWidget> InteractPromptWidget;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CloseModalWidget();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowInteractPrompt(const FText& Text);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideInteractPrompt();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsModalWidgetOpen() const;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void DisableGameplayInput();

	template<typename TWidget>
	TWidget* OpenModalWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	bool ShouldUseTouchControls() const;
	void RefreshProgressDisplay();
	void HandlePieceCollected(int32 PieceIndex);
};

template<typename TWidget>
TWidget* AHousePuzzlePlayerController::OpenModalWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (!WidgetClass)
	{
		return nullptr;
	}

	CloseModalWidget();

	ActiveModalWidget = CreateWidget<UUserWidget>(this, WidgetClass);
	if (!ActiveModalWidget)
	{
		return nullptr;
	}

	ActiveModalWidget->AddToViewport(100);

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(ActiveModalWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	bShowMouseCursor = true;

	return Cast<TWidget>(ActiveModalWidget);
}
