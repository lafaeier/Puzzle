#include "RoomPlayerController.h"
#include "Engine/Engine.h"

void ARoomPlayerController::ShowPrompt(const FString& Text)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Cyan, Text);
	}
}

void ARoomPlayerController::ClearPrompt()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.001f, FColor::Cyan, TEXT(""));
	}
}
