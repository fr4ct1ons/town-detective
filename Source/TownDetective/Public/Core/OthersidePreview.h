// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OthersidePreview.generated.h"

class UCapsuleComponent;
class ATownDetectiveCharacter;

UCLASS()
class TOWNDETECTIVE_API AOthersidePreview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOthersidePreview();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Offset = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCapsuleComponent> Collider;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<USceneComponent> CaptureRoot;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<USceneCaptureComponent2D> PastCapture;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<USceneCaptureComponent2D> PresentCapture;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ATownDetectiveCharacter> Player;

	UPROPERTY(BlueprintReadOnly)
	bool Blocked;

	TArray<UPrimitiveComponent*> OverlappedActors;

	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 OverlappingComponentsNum;
	
	UFUNCTION()
	void OverlapAdded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	UFUNCTION()
	void OverlapRemoved(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Init(ATownDetectiveCharacter* newPlayer, FVector newOffset);

	UFUNCTION(BlueprintCallable)
	void Swap(FVector newPos);

	UFUNCTION(BlueprintPure)
	bool IsBlocked() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Swapped = false;
};
