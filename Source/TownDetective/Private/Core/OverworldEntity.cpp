// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/OverworldEntity.h"


// Sets default values
AOverworldEntity::AOverworldEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOverworldEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverworldEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOverworldEntity::Interact(ATownDetectiveCharacter* playaer)
{
}

