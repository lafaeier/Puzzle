#include "UI/LockboxWidget.h"
#include "Puzzles/Bedroom/BedroomLockbox.h"
#include "HousePuzzlePlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULockboxWidget::InitializeLockbox(ABedroomLockbox* InLockbox)
{
	Lockbox = InLockbox;
}

void ULockboxWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CurrentCode.Empty();
	UpdateCodeDisplay();

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnConfirmClicked);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnCloseClicked);
	}

	// AddDynamic requires a literal member function pointer; a loop variable crashes at runtime.
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit0"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit0Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit1"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit1Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit2"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit2Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit3"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit3Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit4"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit4Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit5"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit5Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit6"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit6Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit7"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit7Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit8"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit8Clicked);
	}
	if (UButton* DigitButton = Cast<UButton>(GetWidgetFromName(TEXT("Digit9"))))
	{
		DigitButton->OnClicked.AddDynamic(this, &ULockboxWidget::OnDigit9Clicked);
	}
}

void ULockboxWidget::AppendDigit(int32 Digit)
{
	if (CurrentCode.Len() >= 3)
	{
		return;
	}

	CurrentCode.Append(FString::FromInt(Digit));
	UpdateCodeDisplay();
}

void ULockboxWidget::OnConfirmClicked()
{
	if (Lockbox)
	{
		Lockbox->SubmitCode(CurrentCode);

		if (Lockbox->LockboxState == ELockboxState::Open)
		{
			if (APlayerController* PC = GetOwningPlayer())
			{
				if (AHousePuzzlePlayerController* PuzzlePC = Cast<AHousePuzzlePlayerController>(PC))
				{
					PuzzlePC->CloseModalWidget();
				}
			}
		}
		else
		{
			CurrentCode.Empty();
			UpdateCodeDisplay();
		}
	}
}

void ULockboxWidget::OnCloseClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AHousePuzzlePlayerController* PuzzlePC = Cast<AHousePuzzlePlayerController>(PC))
		{
			PuzzlePC->CloseModalWidget();
		}
	}
}

void ULockboxWidget::UpdateCodeDisplay()
{
	if (CodeDisplayText)
	{
		FString Display = CurrentCode;
		while (Display.Len() < 3)
		{
			Display.AppendChar(TEXT('-'));
		}
		CodeDisplayText->SetText(FText::FromString(Display));
	}
}
