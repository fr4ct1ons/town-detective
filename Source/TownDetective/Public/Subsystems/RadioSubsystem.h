// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RadioSubsystem.generated.h"

class ARadioSignal;
/**
 * 
 */
UCLASS()
class TOWNDETECTIVE_API URadioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<ARadioSignal*> RadioSignals;
	
public:
	UFUNCTION()
	void RegisterRadio(ARadioSignal* radio);
	UFUNCTION()
	void UnregisterRadio(ARadioSignal* radio);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ARadioSignal*>& GetEmittingSignals();

};
