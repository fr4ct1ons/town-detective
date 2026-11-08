// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadioSignalEntry.h"
#include "Blueprint/UserWidget.h"
#include "RadioUI.generated.h"

class UVerticalBox;
/**
 * 
 */
UCLASS()
class TOWNDETECTIVE_API URadioUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UVerticalBox> SignalList;

	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void AddSignalEntry(URadioSignalEntry* Entry);
};
