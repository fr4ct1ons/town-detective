// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/OthersidePreview.h"

#include "TownDetectiveCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
AOthersidePreview::AOthersidePreview()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	//Collider->InitCapsuleSize(40, 80);
	Collider->SetEnableGravity(false);
	Collider->SetGenerateOverlapEvents(true);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AOthersidePreview::OverlapAdded);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AOthersidePreview::OverlapRemoved);
	
	RootComponent = Collider;


	
	CaptureRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Captures Root"));
	CaptureRoot->SetupAttachment(RootComponent);
	
	PastCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Past Scene Capture"));
	PastCapture->SetupAttachment(CaptureRoot);
	
	PresentCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Present Scene Capture"));
	PresentCapture->SetupAttachment(CaptureRoot);

	PresentCapture->Deactivate();
	PresentCapture->SetVisibility(false);
}

// Called when the game starts or when spawned
void AOthersidePreview::BeginPlay()
{
	Super::BeginPlay();
}

void AOthersidePreview::OverlapAdded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent
                                     * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappingComponentsNum++;
}

void AOthersidePreview::OverlapRemoved(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingComponentsNum--;
}

// Called every frame
void AOthersidePreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Player != nullptr)
	{
		SetActorLocation(Player->GetActorLocation() + (Swapped ? -Offset : Offset));
		CaptureRoot->SetWorldRotation(Player->GetFirstPersonCameraComponent()->GetComponentRotation());
	}

	// Might be faster to just use events
	/*
	Collider->GetOverlappingComponents(OverlappedActors);
	if(OverlappedActors.Num() > 0)
	{
		Blocked = true;
	}
	else
	{
		Blocked = false;
	}
	*/

	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Magenta, TEXT("Colliders: " + FString::FromInt(Blocked)));
}

void AOthersidePreview::Init(ATownDetectiveCharacter* newPlayer, FVector newOffset)
{
	Player = newPlayer;

	Offset = newOffset;
	SetActorLocation(Player->GetActorLocation() + (Swapped ? -Offset : Offset));
}

void AOthersidePreview::Swap(FVector newPos)
{
	SetActorLocation(newPos);
	PresentCapture->ToggleActive();
	PresentCapture->ToggleVisibility();

	PastCapture->ToggleActive();
	PastCapture->ToggleVisibility();
	Swapped = !Swapped;
}

bool AOthersidePreview::IsBlocked() const
{
	return OverlappingComponentsNum > 0;
}

