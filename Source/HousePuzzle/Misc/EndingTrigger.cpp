#include "Misc/EndingTrigger.h"
#include "HousePuzzlePlayerController.h"
#include "UI/EndingWidget.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

AEndingTrigger::AEndingTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	SetRootComponent(TriggerVolume);
	TriggerVolume->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
	TriggerVolume->SetGenerateOverlapEvents(true);
}

void AEndingTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bHasTriggered)
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character || !Character->IsPlayerControlled())
	{
		return;
	}

	bHasTriggered = true;

	if (AHousePuzzlePlayerController* PC = Cast<AHousePuzzlePlayerController>(Character->GetController()))
	{
		PC->DisableGameplayInput();

		if (EndingWidgetClass)
		{
			PC->OpenModalWidget<UEndingWidget>(EndingWidgetClass);
		}
	}
}

void AEndingTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AEndingTrigger::OnOverlapBegin);
}
