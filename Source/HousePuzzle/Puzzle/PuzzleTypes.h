#pragma once

#include "CoreMinimal.h"
#include "PuzzleTypes.generated.h"

UENUM(BlueprintType)
enum class EPuzzleId : uint8
{
	Bedroom     UMETA(DisplayName = "Bedroom"),
	Balcony     UMETA(DisplayName = "Balcony"),
	LivingRoom  UMETA(DisplayName = "LivingRoom"),
	Study       UMETA(DisplayName = "Study"),
	COUNT       UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EChimeColor : uint8
{
	Red,
	Yellow,
	Blue,
	Green,
	Purple
};

UENUM(BlueprintType)
enum class ESlideType : uint8
{
	Sun,
	Moon,
	Star,
	Cloud
};

UENUM(BlueprintType)
enum class EBookSymbol : uint8
{
	None,
	Circle,
	TriangleUp,
	TriangleDown,
	FilledDiamond,
	Diamond
};

UENUM(BlueprintType)
enum class ELockboxState : uint8
{
	Locked,
	Shaking,
	Open
};

UENUM(BlueprintType)
enum class EBalconyPuzzleState : uint8
{
	InProgress,
	Completed
};

UENUM(BlueprintType)
enum class ESlideProjectorState : uint8
{
	Collecting,
	ReadyToPlay,
	Playing,
	Completed
};

UENUM(BlueprintType)
enum class EShelfPuzzleState : uint8
{
	InProgress,
	Completed
};

USTRUCT(BlueprintType)
struct FPuzzleBoardPiece
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PieceIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TargetPosition = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D CurrentPosition = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPlaced = false;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPuzzleCompleted, EPuzzleId);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPieceCollected, int32);
DECLARE_MULTICAST_DELEGATE(FOnPuzzleBoardCompleted);
