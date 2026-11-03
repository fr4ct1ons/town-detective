// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/CommonDelegates.h"
#include "Public/Core/CarriableItem.h"
#include "ModularHitscanWeapon.generated.h"

class ATownDetectiveCharacter;

UCLASS()
class TOWNDETECTIVE_API AModularHitscanWeapon : public ACarriableItem
{
	GENERATED_BODY()

protected:
	void GetTraceVectors(FVector& StartPoint, FVector& EndPoint);
	virtual void Interact() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 TraceNumber = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinTraceSpread = 0.f;
	float MaxTraceSpread = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Range = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MagazineCapacity = 7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CarriedAmmoCapacity = 35;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentMagazine = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentCarriedAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootingCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFullAuto = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCoolingDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReloading = false;

	virtual void BeginPlay();

	UPROPERTY(BlueprintAssignable)
	FBaseDelegateSignature OnShoot;

	UPROPERTY(BlueprintAssignable)
	FBaseDelegateSignature OnReloadStart;

	UPROPERTY(BlueprintAssignable)
	FBaseDelegateSignature OnReloadComplete;
	

	UFUNCTION(BlueprintCallable)
	bool TryGetPlayerHolder(ATownDetectiveCharacter*& OutPlayer);

	UFUNCTION(BlueprintCallable)
	void CompleteReload();

	
	FTimerHandle ReloadTimerHandle;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const bool CanShoot();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const bool CanReload();

	UFUNCTION(BlueprintCallable)
	bool TryInstantReload();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool NeedsReload();
	void TryReload();

	UFUNCTION()
	int32 GetCarriedAmmo() const {return CurrentCarriedAmmo;}
	int32 GetCurrentMag() const {return CurrentMagazine;}
};
