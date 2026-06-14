#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RoomGameInstance.generated.h"

UCLASS()
class PUZZLE_API URoomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// ===== Main Quest State =====
	UPROPERTY(BlueprintReadOnly, Category = "Progress")
	bool bCabinetOpened = false;

	UPROPERTY(BlueprintReadOnly, Category = "Progress")
	bool bHasKeyToLivingRoom = false;

	// ===== Side Quest State (deferred) =====
	UPROPERTY(BlueprintReadOnly, Category = "Progress")
	bool bHasBulb = false;

	UPROPERTY(BlueprintReadOnly, Category = "Progress")
	bool bLightIsOn = false;

	UPROPERTY(BlueprintReadOnly, Category = "Progress")
	bool bDrawerUnlocked = false;

	// ===== Inventory =====
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FName> InventoryItemIDs;

	virtual void Init() override;

	// ===== API =====
	UFUNCTION(BlueprintCallable, Category = "Progress")
	void MarkCabinetOpened();

	UFUNCTION(BlueprintCallable, Category = "Progress")
	void MarkKeyObtained();

	UFUNCTION(BlueprintCallable, Category = "Progress")
	bool HasKey(FName KeyID) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddInventoryItem(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasInventoryItem(FName ItemID) const;

	UFUNCTION(BlueprintCallable, Category = "Progress")
	void ResetAllProgress();
};
