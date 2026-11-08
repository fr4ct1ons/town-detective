// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/OverworldEntities/RadioSignal.h"
#include "RadioSignalEntry.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class TOWNDETECTIVE_API URadioSignalEntry : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
	
public:
	UFUNCTION(BlueprintCallable)
	void Update(float distance, const FString& string);
};
