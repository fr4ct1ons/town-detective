// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"

#include "Components/TextBlock.h"

void UPlayerHUD::SetInteractionName(FText name)
{
	InteractionBlock->SetText(name);
}

void UPlayerHUD::SetInteractionVisible(bool isVisible)
{
	InteractionBlock->SetVisibility(isVisible? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
