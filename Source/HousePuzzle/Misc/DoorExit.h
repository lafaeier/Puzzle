#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorExit.generated.h"

class UBoxComponent;
class UPuzzleManager;

UCLASS()
class HOUSEPUZZLE_API ADoorExit : public AActor
{
	GENERATED_BODY()

public:
	ADoorExit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bIsLocked = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	TObjectPtr<UBoxComponent> DoorBlocker;

	UFUNCTION(BlueprintCallable, Category = "Door")
	void UnlockDoor();

protected:
	virtual void BeginPlay() override;

	void OnPuzzleBoardCompleted();
	UPuzzleManager* GetPuzzleManager() const;
};
