#include "ptcGameModeBase.h"

#include "PTCPlayerController.h"

AptcGameModeBase::AptcGameModeBase()
{
	PlayerControllerClass = APTCPlayerController::StaticClass();
}