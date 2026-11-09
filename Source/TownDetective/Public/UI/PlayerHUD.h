// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class TOWNDETECTIVE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> InteractionBlock;

public:
	void SetInteractionName(FText name);
	void SetInteractionVisible(bool isVisible);
};
