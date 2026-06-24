#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlayerController.h"
#include "RoomPlayerController.generated.h"

UCLASS()
class PUZZLE_API ARoomPlayerController : public APuzzlePlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPrompt(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ClearPrompt();
};
