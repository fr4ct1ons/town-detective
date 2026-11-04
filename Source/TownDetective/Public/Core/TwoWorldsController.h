// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TwoWorldsController.generated.h"

class AOthersidePreview;
class UActorFolder;

UCLASS()
class TOWNDETECTIVE_API ATwoWorldsController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATwoWorldsController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AActor> PastRootActor;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AActor> PresentRootActor;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AActor> PastReference;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AActor> PresentReference;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AOthersidePreview> Preview;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector PresentToPastOffset;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<AActor*> PastActors;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<AActor*> PresentActors;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bPlayerIsInPast;

	UFUNCTION(BlueprintCallable)
	void SwapPlayer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
