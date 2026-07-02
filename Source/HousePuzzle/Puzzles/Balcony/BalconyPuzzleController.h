#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle/PuzzleTypes.h"
#include "BalconyPuzzleController.generated.h"

class AWindChime;
class APuzzlePiecePickup;
class UPuzzleManager;

UCLASS()
class HOUSEPUZZLE_API ABalconyPuzzleController : public AActor
{
	GENERATED_BODY()

public:
	ABalconyPuzzleController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<EChimeColor> CorrectSequence;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	int32 CurrentIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	EBalconyPuzzleState PuzzleState = EBalconyPuzzleState::InProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<AActor> FlowerPotActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<APuzzlePiecePickup> LinkedPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	FVector FlowerPotHiddenOffset = FVector(-100.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> WrongChimeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> FlowerPotMoveSound;

	void OnChimeClicked(EChimeColor Color, AWindChime* Chime);

protected:
	virtual void BeginPlay() override;

	FVector FlowerPotInitialLocation;
	bool bFlowerPotMoved = false;

	void HandleCorrectChime(AWindChime* Chime);
	void HandleWrongChime();
	void CompletePuzzle();
	void MoveFlowerPot();
	UPuzzleManager* GetPuzzleManager() const;
};
