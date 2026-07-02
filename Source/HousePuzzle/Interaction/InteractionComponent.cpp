#include "Interaction/InteractionComponent.h"
#include "Interaction/InteractableBase.h"
#include "HousePuzzlePlayerController.h"
#include "HousePuzzleCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AHousePuzzlePlayerController* PC = GetPuzzlePlayerController())
	{
		if (PC->IsModalWidgetOpen())
		{
			UpdateInteractPrompt(nullptr);
			CurrentTarget = nullptr;
			return;
		}
	}

	AInteractableBase* HitTarget = LineTraceInteractable();
	if (HitTarget && HitTarget->CanInteract(GetOwner()))
	{
		CurrentTarget = HitTarget;
		UpdateInteractPrompt(CurrentTarget);
	}
	else
	{
		CurrentTarget = nullptr;
		UpdateInteractPrompt(nullptr);
	}
}

void UInteractionComponent::PerformInteract()
{
	if (!CurrentTarget || !CurrentTarget->CanInteract(GetOwner()))
	{
		return;
	}

	CurrentTarget->OnInteract(GetOwner());
}

AInteractableBase* UInteractionComponent::LineTraceInteractable() const
{
	const AHousePuzzleCharacter* Character = Cast<AHousePuzzleCharacter>(GetOwner());
	if (!Character)
	{
		return nullptr;
	}

	const UCameraComponent* Camera = Character->GetFirstPersonCameraComponent();
	if (!Camera)
	{
		return nullptr;
	}

	const FVector Start = Camera->GetComponentLocation();
	const FVector End = Start + Camera->GetForwardVector() * TraceDistance;

	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(InteractTrace), false, GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		return Cast<AInteractableBase>(Hit.GetActor());
	}

	return nullptr;
}

AHousePuzzlePlayerController* UInteractionComponent::GetPuzzlePlayerController() const
{
	if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		return Cast<AHousePuzzlePlayerController>(OwnerPawn->GetController());
	}
	return nullptr;
}

void UInteractionComponent::UpdateInteractPrompt(AInteractableBase* NewTarget)
{
	if (AHousePuzzlePlayerController* PC = GetPuzzlePlayerController())
	{
		if (NewTarget)
		{
			PC->ShowInteractPrompt(NewTarget->GetInteractPrompt());
		}
		else
		{
			PC->HideInteractPrompt();
		}
	}
}
