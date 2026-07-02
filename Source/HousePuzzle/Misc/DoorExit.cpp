#include "Misc/DoorExit.h"
#include "Puzzle/PuzzleManager.h"
#include "Core/HousePuzzleGameInstance.h"
#include "Components/BoxComponent.h"

ADoorExit::ADoorExit()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorBlocker = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorBlocker"));
	SetRootComponent(DoorBlocker);
	DoorBlocker->SetBoxExtent(FVector(20.f, 100.f, 200.f));
	DoorBlocker->SetCollisionProfileName(TEXT("BlockAll"));
}

void ADoorExit::BeginPlay()
{
	Super::BeginPlay();

	if (bIsLocked)
	{
		DoorBlocker->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	if (UPuzzleManager* Manager = GetPuzzleManager())
	{
		if (Manager->IsDoorUnlocked())
		{
			UnlockDoor();
		}
		else
		{
			Manager->OnPuzzleBoardCompleted.AddUObject(this, &ADoorExit::OnPuzzleBoardCompleted);
		}
	}
}

void ADoorExit::UnlockDoor()
{
	bIsLocked = false;
	if (DoorBlocker)
	{
		DoorBlocker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DoorBlocker->SetHiddenInGame(true);
	}
}

void ADoorExit::OnPuzzleBoardCompleted()
{
	UnlockDoor();
}

UPuzzleManager* ADoorExit::GetPuzzleManager() const
{
	if (UHousePuzzleGameInstance* GI = Cast<UHousePuzzleGameInstance>(GetGameInstance()))
	{
		return GI->GetPuzzleManager();
	}
	return nullptr;
}
