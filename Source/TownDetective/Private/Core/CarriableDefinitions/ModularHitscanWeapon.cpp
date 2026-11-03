// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Core/CarriableDefinitions/ModularHitscanWeapon.h"

#include "TownDetectiveCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

void AModularHitscanWeapon::Interact()
{
	if(!CanShoot())
	{
		//return;
		
		if(!TryInstantReload())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Not Reloading.");
			return;
		}
		
	}
	
	FHitResult HitResult;
	
	ATownDetectiveCharacter* outPlayer = nullptr;
	FVector StartPoint;
	FVector EndPoint;
	
	if(TryGetPlayerHolder(outPlayer))
	{

		if(outPlayer != nullptr)
		{
			StartPoint = outPlayer->GetFirstPersonCameraComponent()->GetComponentLocation();
			EndPoint = StartPoint + (outPlayer->GetFirstPersonCameraComponent()->GetForwardVector() * Range);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Error getting player.");
			return;
		}
	}
	else
	{
		StartPoint = GetActorLocation();
		EndPoint = GetActorLocation() + (GetActorForwardVector() * Range);
	}
	
	GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility );

	DrawDebugLine(GetWorld(), StartPoint, HitResult.Location, FColor::Red, true, 67.f, 0, 1.f);
	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, true, 67.f, 0, 1.f);

	if (!FMath::IsNearlyZero(ShootingCooldown))
	{
		FTimerHandle TimerHandle;
		IsCoolingDown = true;
		GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			IsCoolingDown = false;
		}), ShootingCooldown, false);
	}

	CurrentMagazine--;
	OnShoot.Broadcast();
	
	if (NeedsReload())
	{
		TryReload();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Reload is needed - Bullets left:" + CurrentCarriedAmmo);
	}
	
	if(HitResult.bBlockingHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Hit Point:" + HitResult.GetActor()->GetName());
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 20.f, GetInstigatorController(), this, UDamageType::StaticClass());
	}

	Super::Interact();
}

bool AModularHitscanWeapon::TryGetPlayerHolder(ATownDetectiveCharacter*& OutPlayer)
{
	OutPlayer = Cast<ATownDetectiveCharacter>(Holder);

	
	if(OutPlayer == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Failure getting player!");
		return false;
	}
	
	return true;
}

void AModularHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentMagazine = MagazineCapacity;
	CurrentCarriedAmmo = CarriedAmmoCapacity;
}

const bool AModularHitscanWeapon::CanShoot()
{
	if (IsCoolingDown || IsReloading)
	{
		return false;
	}
	
	if(CurrentMagazine <= 0 && MagazineCapacity > 0) 
	{
		return false;
	}

	return true;
	
}

const bool AModularHitscanWeapon::CanReload()
{
	return CurrentMagazine < MagazineCapacity;
}

bool AModularHitscanWeapon::TryInstantReload()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Reloading...");
	
	if(CarriedAmmoCapacity <= 0)
	{
		CurrentMagazine = MagazineCapacity;
		return true;
	}
	
	if(CurrentCarriedAmmo <= 0)
	{
		return false;
	}
	
	int32 overDrawn = 0;
	CurrentCarriedAmmo -= MagazineCapacity;
	if(CurrentCarriedAmmo < 0) //Ammo was overdrawn
	{
		overDrawn =  FMath::Abs(CurrentCarriedAmmo);
		CurrentCarriedAmmo = 0;
	}
	CurrentMagazine = MagazineCapacity - overDrawn;

	IsReloading = false;
	return true;
}

void AModularHitscanWeapon::CompleteReload()
{
	int32 overDrawn = 0;
	int32 requiredBullets = MagazineCapacity - CurrentMagazine;
	CurrentCarriedAmmo -= requiredBullets;
	
	if(CurrentCarriedAmmo < 0) //Ammo was overdrawn
	{
		overDrawn =  FMath::Abs(CurrentCarriedAmmo);
		CurrentCarriedAmmo = 0;
	}
	CurrentMagazine = MagazineCapacity - overDrawn;

	OnReloadComplete.Broadcast();
	IsReloading = false;
}

bool AModularHitscanWeapon::NeedsReload()
{
	if(CurrentMagazine <= 0) 
	{
		return true;
	}

	return false;
}

void AModularHitscanWeapon::TryReload()
{
	if (CurrentMagazine >= MagazineCapacity || CurrentCarriedAmmo <= 0)
	{
		return;
	}
	
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		
		IsReloading = true;
		OnReloadStart.Broadcast();
	}), 0.1f, false);
}


