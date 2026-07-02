#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HousePuzzleGameInstance.generated.h"

class UPuzzleManager;

UCLASS()
class HOUSEPUZZLE_API UHousePuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	UPuzzleManager* GetPuzzleManager() const;
};
