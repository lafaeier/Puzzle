#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RoomSaveGame.generated.h"

UCLASS()
class PUZZLE_API URoomSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bCabinetOpened = false;

	UPROPERTY()
	bool bHasKeyToLivingRoom = false;

	UPROPERTY()
	bool bHasBulb = false;

	UPROPERTY()
	bool bLightIsOn = false;

	UPROPERTY()
	bool bDrawerUnlocked = false;

	UPROPERTY()
	TArray<FName> InventoryItemIDs;

	UPROPERTY()
	FName CurrentLevel;

	/** Copy state from a URoomGameInstance into this save object. */
	void CaptureFrom(const class URoomGameInstance* GI, FName InCurrentLevel);

	/** Restore state from this save object into a URoomGameInstance. */
	void RestoreTo(class URoomGameInstance* GI) const;
};
