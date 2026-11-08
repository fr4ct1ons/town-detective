// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RadioUI/RadioSignalEntry.h"

#include "Components/TextBlock.h"

void URadioSignalEntry::Update(float distance, const FString& string)
{

	FNumberFormattingOptions format;
	format.MinimumFractionalDigits = 2;
	format.MaximumFractionalDigits = 2;
	TextBlock->SetText(FText::FromString(FText::AsNumber(distance/100.f, &format).ToString() + " - " + string));
}
