#include "PickupItem.h"
#include "InventoryComponent.h"
#include "Core/RoomGameInstance.h"
#include "Puzzle.h"

void APickupItem::Interact_Implementation(APawn* Interactor)
{
	UInventoryComponent* Inv = Interactor->FindComponentByClass<UInventoryComponent>();
	if (Inv)
	{
		Inv->AddItem(ItemID);
	}

	URoomGameInstance* GI = GetGameInstance<URoomGameInstance>();
	if (GI)
	{
		GI->AddInventoryItem(ItemID);
		if (ItemID == FName(TEXT("KeyToLivingRoom")))
		{
			GI->MarkKeyObtained();
		}
	}

	UE_LOG(LogPuzzle, Log, TEXT("Picked up: %s (ID: %s)"), *ItemName.ToString(), *ItemID.ToString());
	Destroy();
}

FString APickupItem::GetInteractPrompt_Implementation() const
{
	return FString::Printf(TEXT("Press F to pick up %s"), *ItemName.ToString());
}
