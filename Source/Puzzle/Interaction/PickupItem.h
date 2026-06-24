#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "PickupItem.generated.h"

UCLASS()
class PUZZLE_API APickupItem : public AInteractableActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ItemName;

	virtual void Interact_Implementation(APawn* Interactor) override;
	virtual FString GetInteractPrompt_Implementation() const override;
};
