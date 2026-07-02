#include "Puzzles/Bedroom/BedroomPhotoFrame.h"
#include "Components/DecalComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"

ABedroomPhotoFrame::ABedroomPhotoFrame()
{
	InteractPromptText = FText::FromString(TEXT("Press E to flip photo frame"));

	BackDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("BackDecal"));
	BackDecal->SetupAttachment(RootComponent);
	BackDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	BackDecal->DecalSize = FVector(20.f, 20.f, 20.f);
	BackDecal->SetVisibility(false);

	FlipTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FlipTimeline"));
	FlipTimeline->SetTimelineLength(0.5f);
}

void ABedroomPhotoFrame::OnInteract(AActor* Interactor)
{
	if (!CanInteract(Interactor) || bIsFlipped)
	{
		return;
	}

	Super::OnInteract(Interactor);

	bIsFlipped = true;
	InitialRotation = GetActorRotation();
	TargetRotation = InitialRotation + FRotator(0.f, 180.f, 0.f);

	if (FlipCurve)
	{
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("OnFlipTimelineUpdate"));
		FlipTimeline->AddInterpFloat(FlipCurve, TimelineCallback);

		FOnTimelineEvent FinishedCallback;
		FinishedCallback.BindUFunction(this, FName("OnFlipTimelineFinished"));
		FlipTimeline->SetTimelineFinishedFunc(FinishedCallback);

		FlipTimeline->PlayFromStart();
	}
	else
	{
		SetActorRotation(TargetRotation);
		if (BackDecal)
		{
			BackDecal->SetVisibility(true);
		}
	}
}

void ABedroomPhotoFrame::OnFlipTimelineUpdate(float Value)
{
	const FRotator NewRotation = FMath::Lerp(InitialRotation, TargetRotation, Value);
	SetActorRotation(NewRotation);
}

void ABedroomPhotoFrame::OnFlipTimelineFinished()
{
	if (BackDecal)
	{
		BackDecal->SetVisibility(true);
	}
}
