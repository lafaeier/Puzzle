#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "Puzzle/PuzzleTypes.h"
#include "BedroomLockbox.generated.h"

class ULockboxWidget;
class APuzzlePiecePickup;
class UPuzzleManager;
class USoundBase;

UCLASS()
class HOUSEPUZZLE_API ABedroomLockbox : public AInteractableBase
{
	GENERATED_BODY()

public:
	ABedroomLockbox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	FString CorrectCode = TEXT("371");

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	ELockboxState LockboxState = ELockboxState::Locked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<ULockboxWidget> LockboxWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<APuzzlePiecePickup> LinkedPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> RejectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> OpenSound;

	virtual void OnInteract(AActor* Interactor) override;
	virtual bool CanInteract(AActor* Interactor) const override;

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void SubmitCode(const FString& Code);

protected:
	FTimerHandle ShakeTimerHandle;

	void OpenLockbox();
	void PlayRejectFeedback();
	void EndShake();
	UPuzzleManager* GetPuzzleManager() const;
};
