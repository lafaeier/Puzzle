#include "RoomGameInstance.h"
#include "Puzzle.h"

void URoomGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogPuzzle, Log, TEXT("[RoomGameInstance] INIT — all state flags defaulted to false, inventory empty. Ready for Phase 2."));
}

void URoomGameInstance::MarkCabinetOpened()
{
	bCabinetOpened = true;
	UE_LOG(LogPuzzle, Log, TEXT("[RoomGameInstance] Cabinet opened."));
}

void URoomGameInstance::MarkKeyObtained()
{
	bHasKeyToLivingRoom = true;
	UE_LOG(LogPuzzle, Log, TEXT("[RoomGameInstance] Key to LivingRoom obtained."));
}

bool URoomGameInstance::HasKey(FName KeyID) const
{
	return InventoryItemIDs.Contains(KeyID);
}

void URoomGameInstance::AddInventoryItem(FName ItemID)
{
	InventoryItemIDs.AddUnique(ItemID);
	UE_LOG(LogPuzzle, Log, TEXT("[RoomGameInstance] Item added: %s"), *ItemID.ToString());
}

bool URoomGameInstance::HasInventoryItem(FName ItemID) const
{
	return InventoryItemIDs.Contains(ItemID);
}

void URoomGameInstance::ResetAllProgress()
{
	bCabinetOpened = false;
	bHasKeyToLivingRoom = false;
	bHasBulb = false;
	bLightIsOn = false;
	bDrawerUnlocked = false;
	InventoryItemIDs.Empty();
	UE_LOG(LogPuzzle, Log, TEXT("[RoomGameInstance] All progress reset."));
}
