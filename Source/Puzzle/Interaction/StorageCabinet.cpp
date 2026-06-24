#include "StorageCabinet.h"
#include "PickupItem.h"
#include "Core/RoomGameInstance.h"
#include "Engine/World.h"
#include "Puzzle.h"

void AStorageCabinet::Interact_Implementation(APawn* Interactor)
{
	if (bOpened)
	{
		UE_LOG(LogPuzzle, Verbose, TEXT("StorageCabinet already opened — ignoring"));
		return;
	}

	bOpened = true;

	URoomGameInstance* GI = GetGameInstance<URoomGameInstance>();
	if (GI)
	{
		GI->MarkCabinetOpened();
	}

	if (SpawnItemClass)
	{
		FTransform WorldSpawn = SpawnTransform * GetActorTransform();
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<APickupItem>(SpawnItemClass, WorldSpawn, Params);

		UE_LOG(LogPuzzle, Log, TEXT("StorageCabinet: spawned pickup item"));
	}
}

FString AStorageCabinet::GetInteractPrompt_Implementation() const
{
	return bOpened ? TEXT("The cabinet is already open") : TEXT("Press F to open cabinet");
}
