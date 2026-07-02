#include "UI/ProgressWidget.h"
#include "Components/TextBlock.h"

void UProgressWidget::UpdateProgress(int32 Collected, int32 Total)
{
	if (ProgressTextBlock)
	{
		ProgressTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Pieces %d/%d"), Collected, Total)));
	}
}
