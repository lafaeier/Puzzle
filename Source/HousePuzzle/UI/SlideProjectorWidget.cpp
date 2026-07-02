#include "UI/SlideProjectorWidget.h"
#include "Puzzles/LivingRoom/SlideProjector.h"
#include "HousePuzzlePlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

namespace
{
FString SlideTypeToString(ESlideType Type)
{
	switch (Type)
	{
	case ESlideType::Sun: return TEXT("Sun");
	case ESlideType::Moon: return TEXT("Moon");
	case ESlideType::Star: return TEXT("Star");
	case ESlideType::Cloud: return TEXT("Cloud");
	default: return TEXT("?");
	}
}
}

void USlideProjectorWidget::InitializeProjector(ASlideProjector* InProjector)
{
	Projector = InProjector;
}

void USlideProjectorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayOrder.Empty();
	UpdateOrderDisplay();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &USlideProjectorWidget::OnPlayClicked);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &USlideProjectorWidget::OnCloseClicked);
	}

	// AddDynamic requires a literal member function pointer; a loop variable crashes at runtime.
	if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("SunButton"))))
	{
		Button->OnClicked.AddDynamic(this, &USlideProjectorWidget::OnSunClicked);
	}
	if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("MoonButton"))))
	{
		Button->OnClicked.AddDynamic(this, &USlideProjectorWidget::OnMoonClicked);
	}
	if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("StarButton"))))
	{
		Button->OnClicked.AddDynamic(this, &USlideProjectorWidget::OnStarClicked);
	}
	if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("CloudButton"))))
	{
		Button->OnClicked.AddDynamic(this, &USlideProjectorWidget::OnCloudClicked);
	}
}

void USlideProjectorWidget::AppendSlide(ESlideType SlideType)
{
	if (PlayOrder.Num() >= 4)
	{
		return;
	}

	if (InsertSlideSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InsertSlideSound);
	}

	PlayOrder.Add(SlideType);
	UpdateOrderDisplay();
}

void USlideProjectorWidget::OnPlayClicked()
{
	bool bSuccess = false;
	if (Projector)
	{
		bSuccess = Projector->ValidateAndPlay(PlayOrder);
	}

	if (bSuccess)
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
		PlayOrder.Empty();
		UpdateOrderDisplay();
	}
}

void USlideProjectorWidget::OnCloseClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AHousePuzzlePlayerController* PuzzlePC = Cast<AHousePuzzlePlayerController>(PC))
		{
			PuzzlePC->CloseModalWidget();
		}
	}
}

void USlideProjectorWidget::UpdateOrderDisplay()
{
	if (!OrderDisplayText)
	{
		return;
	}

	if (PlayOrder.IsEmpty())
	{
		OrderDisplayText->SetText(FText::FromString(TEXT("Select slide order")));
		return;
	}

	FString Display;
	for (int32 Index = 0; Index < PlayOrder.Num(); ++Index)
	{
		if (Index > 0)
		{
			Display.Append(TEXT(" -> "));
		}
		Display.Append(SlideTypeToString(PlayOrder[Index]));
	}

	OrderDisplayText->SetText(FText::FromString(Display));
}
