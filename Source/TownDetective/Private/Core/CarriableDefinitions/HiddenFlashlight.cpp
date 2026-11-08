// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CarriableDefinitions/HiddenFlashlight.h"

#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Misc/StringBuilder.h"

// Sets default values
AHiddenFlashlight::AHiddenFlashlight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	Light = CreateDefaultSubobject<USpotLightComponent>(FName("Light"));
	Light->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHiddenFlashlight::BeginPlay()
{
	Super::BeginPlay();
	HiddenLightMPCInstance = GetWorld()->GetParameterCollectionInstance(HiddenLightMPC);
}

void AHiddenFlashlight::Interact()
{
	Super::Interact();
	Light->SetVisibility(!Light->IsVisible());

	HiddenLightMPCInstance->SetScalarParameterValue(FName("Enabled"), Light->IsVisible() ? 1.0f : 0.0f);
	HiddenLightMPCInstance->SetScalarParameterValue(FName("Intensity"), Light->Intensity);
}

// Called every frame
void AHiddenFlashlight::Tick(float DeltaTime)
{
	/*
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Green, "ActorLocation: " + UKismetStringLibrary::Conv_VectorToString(GetActorLocation()));
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Green, "CompLocation: " + UKismetStringLibrary::Conv_VectorToString(Light->GetComponentLocation()));
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Green, "AttenRadius: " + UKismetStringLibrary::Conv_DoubleToString(Light->AttenuationRadius));
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Green, "OuterConeAngle: " + UKismetStringLibrary::Conv_DoubleToString(Light->OuterConeAngle));
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Green, "OuterConeAngleRadians: " + UKismetStringLibrary::Conv_DoubleToString(FMath::DegreesToRadians(Light->OuterConeAngle)));
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Green, "OuterConeCos: " + UKismetStringLibrary::Conv_DoubleToString(FMath::Cos(FMath::DegreesToRadians(Light->OuterConeAngle))));
	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Green, "Direction: " + UKismetStringLibrary::Conv_VectorToString(Light->GetForwardVector()));
	*/
	Super::Tick(DeltaTime);
	HiddenLightMPCInstance->SetVectorParameterValue(FName("Position"), GetActorLocation());
	HiddenLightMPCInstance->SetVectorParameterValue(FName("Direction"), Light->GetForwardVector());
	
	HiddenLightMPCInstance->SetScalarParameterValue(FName("AttenuationRadius"), Light->AttenuationRadius);
	HiddenLightMPCInstance->SetScalarParameterValue(FName("InnerAngleCos"), Light->InnerConeAngle);
	HiddenLightMPCInstance->SetScalarParameterValue(FName("OuterAngleCos"), FMath::Cos(FMath::DegreesToRadians(Light->OuterConeAngle/1.f)));
	HiddenLightMPCInstance->SetScalarParameterValue(FName("OuterAngle"), Light->OuterConeAngle);
}

void AHiddenFlashlight::Enable()
{
	Super::Enable();
}

void AHiddenFlashlight::Disable()
{
	Super::Disable();
	Light->SetVisibility(false);
}
