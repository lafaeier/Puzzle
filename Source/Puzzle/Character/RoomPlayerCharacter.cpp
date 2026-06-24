#include "RoomPlayerCharacter.h"
#include "RoomPlayerController.h"
#include "InventoryComponent.h"
#include "Interaction/IInteractable.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Puzzle.h"

ARoomPlayerCharacter::ARoomPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void ARoomPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARoomPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &ARoomPlayerCharacter::OnInteract);
	}
}

void ARoomPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHoverPrompt();
}

void ARoomPlayerCharacter::UpdateHoverPrompt()
{
	ARoomPlayerController* PC = Cast<ARoomPlayerController>(GetController());
	if (!PC) return;

	UCameraComponent* Camera = GetFirstPersonCameraComponent();
	if (!Camera) return;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * InteractRange;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FString NewPrompt;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<UInteractable>())
		{
			NewPrompt = IInteractable::Execute_GetInteractPrompt(HitActor);
		}
	}

	if (NewPrompt != CurrentPrompt)
	{
		CurrentPrompt = NewPrompt;
		if (!NewPrompt.IsEmpty())
		{
			PC->ShowPrompt(NewPrompt);
		}
		else
		{
			PC->ClearPrompt();
		}
	}
}

void ARoomPlayerCharacter::OnInteract()
{
	UCameraComponent* Camera = GetFirstPersonCameraComponent();
	if (!Camera) return;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * InteractRange;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<UInteractable>())
		{
			UE_LOG(LogPuzzle, Log, TEXT("Interact with: %s"), *HitActor->GetName());
			IInteractable::Execute_Interact(HitActor, this);
		}
	}
}
