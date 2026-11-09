// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverworldEntity.generated.h"

class ATownDetectiveCharacter;

UCLASS()
class TOWNDETECTIVE_API AOverworldEntity : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOverworldEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText InteractionName = FText::FromString("Interact");

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(ATownDetectiveCharacter* player);

	UFUNCTION()
	FText GetInteractionName();
};
