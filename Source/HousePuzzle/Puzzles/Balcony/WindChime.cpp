#include "Puzzles/Balcony/WindChime.h"
#include "Puzzles/Balcony/BalconyPuzzleController.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

AWindChime::AWindChime()
{
	InteractPromptText = FText::FromString(TEXT("Press E to ring chime"));

	HighlightLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("HighlightLight"));
	HighlightLight->SetupAttachment(RootComponent);
	HighlightLight->SetIntensity(0.f);
	HighlightLight->SetLightColor(FLinearColor::Yellow);
	HighlightLight->SetAttenuationRadius(100.f);
}

void AWindChime::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor))
	{
		return;
	}

	Super::OnInteract(Interactor);

	if (PuzzleController)
	{
		PuzzleController->OnChimeClicked(ChimeColor, this);
	}
}

void AWindChime::ActivateChime()
{
	bIsActivated = true;

	if (HighlightLight)
	{
		HighlightLight->SetIntensity(3000.f);
	}

	if (ChimeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ChimeSound, GetActorLocation(), 1.f, PitchMultiplier);
	}
}
