#include "InteractableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Puzzle.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

void AInteractableActor::Interact_Implementation(APawn* Interactor)
{
	UE_LOG(LogPuzzle, Verbose, TEXT("%s: base Interact called — override in subclass"), *GetName());
}

FString AInteractableActor::GetInteractPrompt_Implementation() const
{
	return PromptText;
}
