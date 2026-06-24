#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "InteractableActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class PUZZLE_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInteractableActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FString PromptText;

	virtual void Interact_Implementation(APawn* Interactor) override;
	virtual FString GetInteractPrompt_Implementation() const override;
};
