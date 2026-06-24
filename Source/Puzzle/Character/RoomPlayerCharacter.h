#pragma once

#include "CoreMinimal.h"
#include "PuzzleCharacter.h"
#include "RoomPlayerCharacter.generated.h"

class UInputAction;
class UInventoryComponent;

UCLASS()
class PUZZLE_API ARoomPlayerCharacter : public APuzzleCharacter
{
	GENERATED_BODY()

public:
	ARoomPlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float InteractRange = 300.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UInventoryComponent* InventoryComponent;

	void OnInteract();

private:
	void UpdateHoverPrompt();

	FString CurrentPrompt;
};
