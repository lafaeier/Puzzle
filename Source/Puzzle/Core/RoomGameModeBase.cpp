#include "RoomGameModeBase.h"
#include "Character/RoomHUD.h"

ARoomGameModeBase::ARoomGameModeBase()
{
	HUDClass = ARoomHUD::StaticClass();
}
