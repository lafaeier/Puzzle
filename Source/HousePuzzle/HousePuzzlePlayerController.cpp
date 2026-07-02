// Copyright Epic Games, Inc. All Rights Reserved.

#include "HousePuzzlePlayerController.h"
#include "Core/HousePuzzleGameInstance.h"
#include "Puzzle/PuzzleManager.h"
#include "UI/InteractPromptWidget.h"
#include "UI/ProgressWidget.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "HousePuzzleCameraManager.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "HousePuzzle.h"
#include "Widgets/Input/SVirtualJoystick.h"

AHousePuzzlePlayerController::AHousePuzzlePlayerController()
{
	PlayerCameraManagerClass = AHousePuzzleCameraManager::StaticClass();
}

void AHousePuzzlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);
		if (MobileControlsWidget)
		{
			MobileControlsWidget->AddToPlayerScreen(0);
		}
		else
		{
			UE_LOG(LogHousePuzzle, Error, TEXT("Could not spawn mobile controls widget."));
		}
	}

	if (!IsLocalPlayerController())
	{
		return;
	}

	if (ProgressWidgetClass)
	{
		ProgressWidget = CreateWidget<UProgressWidget>(this, ProgressWidgetClass);
		if (ProgressWidget)
		{
			ProgressWidget->AddToViewport();
		}
	}

	if (InteractPromptWidgetClass)
	{
		InteractPromptWidget = CreateWidget<UInteractPromptWidget>(this, InteractPromptWidgetClass);
		if (InteractPromptWidget)
		{
			InteractPromptWidget->AddToViewport();
			InteractPromptWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		if (UPuzzleManager* Manager = GI->GetPuzzleManager())
		{
			Manager->OnPieceCollected.AddUObject(this, &AHousePuzzlePlayerController::HandlePieceCollected);
			RefreshProgressDisplay();
		}
	}
}

void AHousePuzzlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				if (CurrentContext)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}

			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					if (CurrentContext)
					{
						Subsystem->AddMappingContext(CurrentContext, 0);
					}
				}
			}
		}
	}
}

void AHousePuzzlePlayerController::CloseModalWidget()
{
	if (ActiveModalWidget)
	{
		ActiveModalWidget->RemoveFromParent();
		ActiveModalWidget = nullptr;
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}

void AHousePuzzlePlayerController::ShowInteractPrompt(const FText& Text)
{
	if (InteractPromptWidget)
	{
		InteractPromptWidget->SetPromptText(Text);
		InteractPromptWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void AHousePuzzlePlayerController::HideInteractPrompt()
{
	if (InteractPromptWidget)
	{
		InteractPromptWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

bool AHousePuzzlePlayerController::IsModalWidgetOpen() const
{
	return ActiveModalWidget != nullptr;
}

void AHousePuzzlePlayerController::DisableGameplayInput()
{
	DisableInput(this);
}

void AHousePuzzlePlayerController::RefreshProgressDisplay()
{
	if (!ProgressWidget)
	{
		return;
	}

	int32 Collected = 0;
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		if (UPuzzleManager* Manager = GI->GetPuzzleManager())
		{
			Collected = Manager->GetCollectedPieceCount();
		}
	}

	ProgressWidget->UpdateProgress(Collected, static_cast<int32>(EPuzzleId::COUNT));
}

void AHousePuzzlePlayerController::HandlePieceCollected(int32 PieceIndex)
{
	RefreshProgressDisplay();
}

bool AHousePuzzlePlayerController::ShouldUseTouchControls() const
{
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
