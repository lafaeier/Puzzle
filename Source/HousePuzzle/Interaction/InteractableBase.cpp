#include "Interaction/InteractableBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	SetRootComponent(InteractCollision);
	InteractCollision->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	InteractCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	InteractCollision->SetGenerateOverlapEvents(false);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(InteractCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractPromptText = FText::FromString(TEXT("Press E to interact"));
}

void AInteractableBase::OnInteract(AActor* Interactor)
{
	PlayInteractSound();
}

bool AInteractableBase::CanInteract(AActor* Interactor) const
{
	return bIsEnabled;
}

FText AInteractableBase::GetInteractPrompt() const
{
	return InteractPromptText;
}

void AInteractableBase::PlayInteractSound() const
{
	if (InteractSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, InteractSound, GetActorLocation());
	}
}
