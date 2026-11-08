// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CarriableItem.h"
#include "HiddenFlashlight.generated.h"

class USpotLightComponent;

UCLASS()
class TOWNDETECTIVE_API AHiddenFlashlight : public ACarriableItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHiddenFlashlight();

	virtual void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<USpotLightComponent> Light;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UMaterialParameterCollection> HiddenLightMPC;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UMaterialParameterCollectionInstance> HiddenLightMPCInstance;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Enable() override;
	virtual void Disable() override;
};
