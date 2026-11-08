// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/OverworldEntity.h"
#include "RadioSignal.generated.h"

class URadioUI;
class URadioSignalEntry;

UCLASS()
class TOWNDETECTIVE_API ARadioSignal : public AOverworldEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARadioSignal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float CaptureDistance = 2000.f; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsEmitting = true; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString SignalName; 
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetCaptureDistance();
	FString GetSignalName();
};
