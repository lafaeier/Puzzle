#include "RoomHUD.h"
#include "Engine/Canvas.h"

ARoomHUD::ARoomHUD()
{
}

void ARoomHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas) return;

	float CX = Canvas->ClipX * 0.5f;
	float CY = Canvas->ClipY * 0.5f;

	FCanvasLineItem LineH(FVector2D(CX - CrosshairSize, CY), FVector2D(CX + CrosshairSize, CY));
	LineH.SetColor(CrosshairColor.ToFColor(true));
	LineH.LineThickness = 2.0f;
	Canvas->DrawItem(LineH);

	FCanvasLineItem LineV(FVector2D(CX, CY - CrosshairSize), FVector2D(CX, CY + CrosshairSize));
	LineV.SetColor(CrosshairColor.ToFColor(true));
	LineV.LineThickness = 2.0f;
	Canvas->DrawItem(LineV);
}
