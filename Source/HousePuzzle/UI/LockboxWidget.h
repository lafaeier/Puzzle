#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockboxWidget.generated.h"

class UButton;
class UTextBlock;
class ABedroomLockbox;

UCLASS(Abstract)
class HOUSEPUZZLE_API ULockboxWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeLockbox(ABedroomLockbox* InLockbox);

protected:
	UPROPERTY()
	TObjectPtr<ABedroomLockbox> Lockbox;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> CodeDisplayText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> CloseButton;

	FString CurrentCode;

	virtual void NativeConstruct() override;

	void AppendDigit(int32 Digit);
	void UpdateCodeDisplay();

	UFUNCTION() void OnDigit0Clicked() { AppendDigit(0); }
	UFUNCTION() void OnDigit1Clicked() { AppendDigit(1); }
	UFUNCTION() void OnDigit2Clicked() { AppendDigit(2); }
	UFUNCTION() void OnDigit3Clicked() { AppendDigit(3); }
	UFUNCTION() void OnDigit4Clicked() { AppendDigit(4); }
	UFUNCTION() void OnDigit5Clicked() { AppendDigit(5); }
	UFUNCTION() void OnDigit6Clicked() { AppendDigit(6); }
	UFUNCTION() void OnDigit7Clicked() { AppendDigit(7); }
	UFUNCTION() void OnDigit8Clicked() { AppendDigit(8); }
	UFUNCTION() void OnDigit9Clicked() { AppendDigit(9); }

	UFUNCTION()
	void OnConfirmClicked();

	UFUNCTION()
	void OnCloseClicked();
};
