#include "UI/InteractPromptWidget.h"
#include "Components/TextBlock.h"

void UInteractPromptWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetPromptText(FText::FromString(TEXT("Press E to interact")));
}

void UInteractPromptWidget::SetPromptText(const FText& Text)
{
	if (PromptTextBlock)
	{
		PromptTextBlock->SetText(Text);
	}
}
