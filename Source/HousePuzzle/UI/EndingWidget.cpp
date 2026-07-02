#include "UI/EndingWidget.h"
#include "Components/TextBlock.h"

void UEndingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ShowEnding();
}

void UEndingWidget::ShowEnding()
{
	if (EndingTextBlock)
	{
		EndingTextBlock->SetText(FText::FromString(TEXT("Escape Successful!")));
	}
}
