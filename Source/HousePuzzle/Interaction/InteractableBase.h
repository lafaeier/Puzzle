#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS(Abstract)
class HOUSEPUZZLE_API AInteractableBase : public AActor
{
	GENERATED_BODY()

public:
	AInteractableBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<UBoxComponent> InteractCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractPromptText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TObjectPtr<USoundBase> InteractSound;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void OnInteract(AActor* Interactor);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual bool CanInteract(AActor* Interactor) const;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual FText GetInteractPrompt() const;

protected:
	void PlayInteractSound() const;
};
