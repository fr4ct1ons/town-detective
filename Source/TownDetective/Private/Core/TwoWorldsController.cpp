// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TwoWorldsController.h"

#include "TownDetectiveCharacter.h"
#include "Core/OthersidePreview.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
ATwoWorldsController::ATwoWorldsController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATwoWorldsController::BeginPlay()
{
	Super::BeginPlay();
	PresentToPastOffset = PastReference->GetActorLocation() - PresentReference->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Present to past offset: " + UKismetStringLibrary::Conv_VectorToString(PresentToPastOffset)));

	ATownDetectiveCharacter* player = Cast<ATownDetectiveCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Preview->Init(player, PresentToPastOffset);

	PresentRootActor->GetAttachedActors(PresentActors, true, true);
	PastRootActor->GetAttachedActors(PastActors, true, true);

	TArray<UPrimitiveComponent*> comps;
	for (AActor* actor : PastActors)
	{
		comps.Reset();
		actor->GetComponents(UPrimitiveComponent::StaticClass(), comps);
		for (UPrimitiveComponent* comp : comps)
		{
			comp->SetVisibleInSceneCaptureOnly(true);
		}
	}
	
	//PastRootActor->Children;
}

void ATwoWorldsController::SwapPlayer()
{
	bPlayerIsInPast = !bPlayerIsInPast;
	
	ATownDetectiveCharacter* player = Cast<ATownDetectiveCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector playerPos = player->GetActorLocation();

	player->SetActorLocation(Preview->GetActorLocation());
	
	Preview->Swap(playerPos);

	TArray<UPrimitiveComponent*> comps;
	for (AActor* actor : PastActors)
	{
		comps.Reset();
		actor->GetComponents(UPrimitiveComponent::StaticClass(), comps);
		for (UPrimitiveComponent* comp : comps)
		{
			comp->SetVisibleInSceneCaptureOnly(!bPlayerIsInPast);
		}
	}
	
	for (AActor* actor : PresentActors)
	{
		comps.Reset();
		actor->GetComponents(UPrimitiveComponent::StaticClass(), comps);
		for (UPrimitiveComponent* comp : comps)
		{
			comp->SetVisibleInSceneCaptureOnly(bPlayerIsInPast);
		}
	}
}

// Called every frame
void ATwoWorldsController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

