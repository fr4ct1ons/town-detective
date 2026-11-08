// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/RadioSubsystem.h"

TArray<ARadioSignal*>& URadioSubsystem::GetEmittingSignals()
{
	return RadioSignals;
}

void URadioSubsystem::RegisterRadio(ARadioSignal* radio)
{
	RadioSignals.Add(radio);
}

void URadioSubsystem::UnregisterRadio(ARadioSignal* radio)
{
	RadioSignals.Remove(radio);
}
