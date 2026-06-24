#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RoomHUD.generated.h"

UCLASS()
class PUZZLE_API ARoomHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARoomHUD();

	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	float CrosshairSize = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FLinearColor CrosshairColor = FLinearColor(0.0f, 1.0f, 0.3f, 0.9f);
};
