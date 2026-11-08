// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CarriableItem.h"
#include "UI/RadioUI/RadioSignalEntry.h"
#include "UI/RadioUI/RadioUI.h"
#include "RadioReceiver.generated.h"

class URadioSubsystem;

UCLASS()
class TOWNDETECTIVE_API ARadioReceiver : public ACarriableItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARadioReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<URadioSubsystem> RadioSystem;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<URadioSignalEntry> RadioSignalUIClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<URadioUI> RadioUIClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<URadioUI> RadioUI; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<TObjectPtr<URadioSignalEntry>> RadioSignalWidgets;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Enable() override;
	virtual void Disable() override;
};
