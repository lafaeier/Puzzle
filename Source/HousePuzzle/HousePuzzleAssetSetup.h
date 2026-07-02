#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HousePuzzleAssetSetup.generated.h"

class UCurveFloat;

UCLASS()
class HOUSEPUZZLE_API UHousePuzzleAssetSetup : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Creates or updates /Game/Curves/Curve_PhotoFlip with keys 0->0, 0.5->1, 1->1. Editor only. */
	UFUNCTION(BlueprintCallable, Category = "HousePuzzle|Assets")
	static UCurveFloat* EnsurePhotoFlipCurveAsset();
};
