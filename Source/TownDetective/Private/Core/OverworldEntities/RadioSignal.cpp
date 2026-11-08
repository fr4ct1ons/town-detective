// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/OverworldEntities/RadioSignal.h"

#include "Subsystems/RadioSubsystem.h"


// Sets default values
ARadioSignal::ARadioSignal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARadioSignal::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<URadioSubsystem>()->RegisterRadio(this);
	
}

// Called every frame
void ARadioSignal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ARadioSignal::GetCaptureDistance()
{
	return CaptureDistance;
}

FString ARadioSignal::GetSignalName()
{
	return SignalName;
}

