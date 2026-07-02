#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AInteractableBase;
class AHousePuzzlePlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOUSEPUZZLE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float TraceDistance = 300.f;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<AInteractableBase> CurrentTarget;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void PerformInteract();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AInteractableBase* LineTraceInteractable() const;
	AHousePuzzlePlayerController* GetPuzzlePlayerController() const;
	void UpdateInteractPrompt(AInteractableBase* NewTarget);
};
