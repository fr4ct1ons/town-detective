// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CarriableDefinitions/RadioReceiver.h"

#include "Blueprint/UserWidget.h"
#include "Core/OverworldEntities/RadioSignal.h"
#include "Subsystems/RadioSubsystem.h"
#include "UI/RadioUI/RadioUI.h"
#include "UI/RadioUI/RadioSignalEntry.h"


// Sets default values
ARadioReceiver::ARadioReceiver()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARadioReceiver::BeginPlay()
{
	Super::BeginPlay();

	RadioSystem = GetGameInstance()->GetSubsystem<URadioSubsystem>();
	
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	RadioUI = CreateWidget<URadioUI>(pc, RadioUIClass);

	for (int i = 0; i < 4; ++i)
	{
		URadioSignalEntry* entry = CreateWidget<URadioSignalEntry>(RadioUI, RadioSignalUIClass);
		entry->SetVisibility(ESlateVisibility::Collapsed);
		RadioUI->AddSignalEntry(entry);
		RadioSignalWidgets.Add(entry);
	}
}

// Called every frame
void ARadioReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto radios = RadioSystem->GetEmittingSignals();

	for (int i = 0; i < radios.Num(); ++i)
	{
		ARadioSignal* radio = radios[i];
		
		float distance = FVector::Dist(GetActorLocation(), radio->GetActorLocation());
		
		if (distance <= radio->GetCaptureDistance())
		{
			if (i >= RadioSignalWidgets.Num())
			{
				URadioSignalEntry* entry = CreateWidget<URadioSignalEntry>(RadioUI, RadioSignalUIClass);
				RadioUI->AddSignalEntry(entry);
				RadioSignalWidgets.Add(entry);
			}
			RadioSignalWidgets[i]->SetVisibility(ESlateVisibility::Visible);
			RadioSignalWidgets[i]->Update(distance, radio->GetSignalName());
		}
		else
		{
			RadioSignalWidgets[i]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ARadioReceiver::Enable()
{
	Super::Enable();
	RadioUI->AddToViewport();
}

void ARadioReceiver::Disable()
{
	Super::Disable();
	RadioUI->RemoveFromParent();
}
