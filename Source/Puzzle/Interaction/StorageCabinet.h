#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "StorageCabinet.generated.h"

class APickupItem;

UCLASS()
class PUZZLE_API AStorageCabinet : public AInteractableActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TSubclassOf<APickupItem> SpawnItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	bool bOpened = false;

	virtual void Interact_Implementation(APawn* Interactor) override;
	virtual FString GetInteractPrompt_Implementation() const override;
};
