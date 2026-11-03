// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Core/CarriableItem.h"


// Sets default values
ACarriableItem::ACarriableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarriableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarriableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACarriableItem::Interact()
{
	OnInteract();

	
}


void ACarriableItem::SetHolder(TObjectPtr<AActor> holder, FName socket)
{
	if(IsValid(holder))
	{
		AttachToActor(holder, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), socket);
		Holder = holder;
		HolderSocket = socket;
	}
	
	Holder = holder;
}

void ACarriableItem::SetHolder(TObjectPtr<AActor> holder, TObjectPtr<USceneComponent> holderComponent)
{
	if(IsValid(holder))
	{
		Holder = holder;
		HolderComponent = holderComponent;
		AttachToComponent(HolderComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

