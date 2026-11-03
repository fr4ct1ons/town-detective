// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TownDetectiveGameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class ATownDetectiveGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPaused();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnpaused();

public:
	ATownDetectiveGameMode();
	
	UFUNCTION(BlueprintCallable)
	void InvertPausedState();
};



