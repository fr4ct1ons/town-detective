// Copyright Epic Games, Inc. All Rights Reserved.

#include "TownDetectiveGameMode.h"

#include "TownDetectivePlayerController.h"


ATownDetectiveGameMode::ATownDetectiveGameMode()
{
	// stub
}

void ATownDetectiveGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (bRayTracedLightingEnabled)
	{
		GetWorld()->Exec(GetWorld(), TEXT("r.Upscale.Quality 3"));
		GetWorld()->Exec(GetWorld(), TEXT("r.Upscale.Softness 1"));
		GetWorld()->Exec(GetWorld(), TEXT("r.DynamicGlobalIlluminationMethod 1"));
		GetWorld()->Exec(GetWorld(), TEXT("r.ReflectionMethod 1"));
		GetWorld()->Exec(GetWorld(), TEXT("r.AntiAliasingMethod 4"));
	}
	else
	{
		GetWorld()->Exec(GetWorld(), TEXT("r.Upscale.Quality 0"));
		GetWorld()->Exec(GetWorld(), TEXT("r.Upscale.Softness 0"));
		GetWorld()->Exec(GetWorld(), TEXT("r.DynamicGlobalIlluminationMethod 0"));
		GetWorld()->Exec(GetWorld(), TEXT("r.ReflectionMethod 0"));
		GetWorld()->Exec(GetWorld(), TEXT("r.AntiAliasingMethod 0"));
	}
		
	FString cmd = FString("r.ScreenPercentage ") + FString::SanitizeFloat(GetScreenPercentage());
	GEngine->Exec(nullptr, *cmd);
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

float ATownDetectiveGameMode::GetScreenPercentage() const
{	
	FVector2D Result = FVector2D( 1, 1 );
	float currentRes = GSystemResolution.ResY;
	float multiplier = 1.0f;

	if(bRayTracedLightingEnabled)
	{
		return 75.0f;
	}
	
	multiplier = currentRes / static_cast<float>(DesiredHeight);

	return (1/multiplier) * 100.0f;
}