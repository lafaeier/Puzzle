#include "RoomSaveGame.h"
#include "RoomGameInstance.h"

void URoomSaveGame::CaptureFrom(const URoomGameInstance* GI, FName InCurrentLevel)
{
	if (!GI) return;

	bCabinetOpened      = GI->bCabinetOpened;
	bHasKeyToLivingRoom = GI->bHasKeyToLivingRoom;
	bHasBulb            = GI->bHasBulb;
	bLightIsOn          = GI->bLightIsOn;
	bDrawerUnlocked     = GI->bDrawerUnlocked;
	InventoryItemIDs    = GI->InventoryItemIDs;
	CurrentLevel        = InCurrentLevel;
}

void URoomSaveGame::RestoreTo(URoomGameInstance* GI) const
{
	if (!GI) return;

	GI->bCabinetOpened      = bCabinetOpened;
	GI->bHasKeyToLivingRoom = bHasKeyToLivingRoom;
	GI->bHasBulb            = bHasBulb;
	GI->bLightIsOn          = bLightIsOn;
	GI->bDrawerUnlocked     = bDrawerUnlocked;
	GI->InventoryItemIDs    = InventoryItemIDs;
}
