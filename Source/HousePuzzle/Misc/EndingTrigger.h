#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndingTrigger.generated.h"

class UBoxComponent;
class UEndingWidget;

UCLASS()
class HOUSEPUZZLE_API AEndingTrigger : public AActor
{
	GENERATED_BODY()

public:
	AEndingTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ending")
	TSubclassOf<UEndingWidget> EndingWidgetClass;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ending")
	TObjectPtr<UBoxComponent> TriggerVolume;

	bool bHasTriggered = false;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
