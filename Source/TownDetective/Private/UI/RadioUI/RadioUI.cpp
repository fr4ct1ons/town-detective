// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RadioUI/RadioUI.h"

#include "Components/VerticalBox.h"

void URadioUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SignalList->ClearChildren();
}

void URadioUI::AddSignalEntry(URadioSignalEntry* Entry)
{
	SignalList->AddChild(Entry);
}
