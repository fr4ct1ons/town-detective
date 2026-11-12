// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/OverworldEntity.h"
#include "Door.generated.h"

class UTimelineComponent;

UCLASS()
class TOWNDETECTIVE_API ADoor : public AOverworldEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsOpen;

	virtual void Interact(ATownDetectiveCharacter* player) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void Open();

	UFUNCTION(BlueprintImplementableEvent)
	void Close();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
