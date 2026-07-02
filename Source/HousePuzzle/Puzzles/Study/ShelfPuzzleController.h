#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle/PuzzleTypes.h"
#include "ShelfPuzzleController.generated.h"

class ABookPull;
class APuzzlePiecePickup;
class UPuzzleManager;

UCLASS()
class HOUSEPUZZLE_API AShelfPuzzleController : public AActor
{
	GENERATED_BODY()

public:
	AShelfPuzzleController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<EBookSymbol> CorrectOrder;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	int32 CurrentStep = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Puzzle")
	EShelfPuzzleState PuzzleState = EShelfPuzzleState::InProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<APuzzlePiecePickup> LinkedPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TObjectPtr<AActor> SecretCompartmentActor;

	void OnBookPulled(EBookSymbol Symbol, ABookPull* Book);

protected:
	virtual void BeginPlay() override;

	void CompletePuzzle();
	void EnsureDefaultCorrectOrder();
	void ResolveLinkedPieceIfNeeded();
	UPuzzleManager* GetPuzzleManager() const;

	static const TArray<EBookSymbol>& GetDefaultCorrectOrder();
};
