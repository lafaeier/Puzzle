#include "Puzzles/LivingRoom/SlideItem.h"
#include "Puzzles/LivingRoom/SlideProjector.h"

ASlideItem::ASlideItem()
{
	InteractPromptText = FText::FromString(TEXT("Press E to collect slide"));
}

void ASlideItem::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	if (Projector)
	{
		Projector->InsertSlide(SlideType);
	}

	bIsCollected = true;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	bIsEnabled = false;
}

bool ASlideItem::CanInteract(AActor* Interactor) const
{
	return Super::CanInteract(Interactor) && !bIsCollected;
}
