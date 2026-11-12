// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CarriableItem.h"
#include "CrossWorldDevice.generated.h"

UCLASS()
class TOWNDETECTIVE_API ACrossWorldDevice : public ACarriableItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACrossWorldDevice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
