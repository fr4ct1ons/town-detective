// Copyright Epic Games, Inc. All Rights Reserved.

#include "TownDetectiveGameMode.h"

#include "TownDetectivePlayerController.h"

ATownDetectiveGameMode::ATownDetectiveGameMode()
{
	// stub
}


void ATownDetectiveGameMode::InvertPausedState()
{
	TObjectPtr<ATownDetectivePlayerController> pc = Cast<ATownDetectivePlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	if (!pc->IsPaused())
	{
		pc->SetInputMode(FInputModeGameAndUI());
		pc->SetPause(true);
		pc->SetShowMouseCursor(true);
		OnPaused();
	}
	else
	{
		pc->SetInputMode(FInputModeGameOnly());
		pc->SetShowMouseCursor(false);
		OnUnpaused();
	}
}