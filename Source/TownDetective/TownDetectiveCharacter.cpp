// Copyright Epic Games, Inc. All Rights Reserved.

#include "TownDetectiveCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TownDetective.h"
#include "TownDetectiveGameMode.h"
#include "Public/Core/CarriableItem.h"
#include "Public/Core/CarriableDefinitions/ModularHitscanWeapon.h"

ATownDetectiveCharacter::ATownDetectiveCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	HandR = CreateDefaultSubobject<USceneComponent>(TEXT("HandR"));
	HandR->SetupAttachment(GetFirstPersonCameraComponent());

	CurrentStamina = MaxStamina;
}

void ATownDetectiveCharacter::BeginPlay()
{
	Super::BeginPlay();

	bool DefaultSet = false;
	for (TSubclassOf<ACarriableItem> def : StarterCarriables)
	{
		auto temp = GetWorld()->SpawnActor(def);
		ACarriableItem* carriable = Cast<ACarriableItem>(temp);
		carriable->SetHolder(this, HandR);
		carriable->SetActorRelativeLocation(FVector::ZeroVector);
		CurrentCarriables.Add(carriable);
		if(!DefaultSet)
		{
			CurrentCarriable = carriable;
			DefaultSet = true;
			CurrentCarriable->Enable();
		}
		else
		{
			carriable->Disable();
		}
	}
}


void ATownDetectiveCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (StaminaRegenerating && CurrentStamina < MaxStamina)
	{
		CurrentStamina += StaminaRegenRate * DeltaSeconds;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f, MaxStamina);
		//HUD->OnStaminaUpdated.Broadcast(CurrentStamina, MaxStamina);
	}
}



void ATownDetectiveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATownDetectiveCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATownDetectiveCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATownDetectiveCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATownDetectiveCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATownDetectiveCharacter::LookInput);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATownDetectiveCharacter::Fire);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ATownDetectiveCharacter::Reload);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ATownDetectiveCharacter::Pause);
		EnhancedInputComponent->BindAction(ItemSelectionAction, ETriggerEvent::Triggered, this, &ATownDetectiveCharacter::DoItemSelection);
	}
	else
	{
		UE_LOG(LogTownDetective, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ATownDetectiveCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ATownDetectiveCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ATownDetectiveCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ATownDetectiveCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ATownDetectiveCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ATownDetectiveCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ATownDetectiveCharacter::Fire(const FInputActionValue& Value)
{
	if(IsValid(CurrentCarriable))
	{
		CurrentCarriable->Interact();
	}
}

void ATownDetectiveCharacter::Reload(const FInputActionValue& Value)
{
	if(IsValid(CurrentCarriable))
	{
		if (AModularHitscanWeapon* weapon = Cast<AModularHitscanWeapon>(CurrentCarriable))
		{
			weapon->TryReload();
		}
	}
}

void ATownDetectiveCharacter::Pause(const FInputActionValue& Value)
{
	ATownDetectiveGameMode* gm = GetWorld()->GetAuthGameMode<ATownDetectiveGameMode>();

	gm->InvertPausedState();
}


void ATownDetectiveCharacter::DoItemSelection(const FInputActionValue& value)
{
	float indexFloat = value.Get<float>();

	int32 index = FMath::RoundToInt32(indexFloat);
	index--;

	if (index >= 0 && index < CurrentCarriables.Num())
	{
		CurrentCarriable->Disable();
		CurrentCarriable = CurrentCarriables[index];
		CurrentCarriable->Enable();
	}
}


void ATownDetectiveCharacter::ResetStaminaRegen()
{
	StaminaRegenerating = false;

	FTimerHandle unusedTimer;
	
	if (GetWorldTimerManager().TimerExists(StaminaRegenTimer))
	{
		GetWorldTimerManager().ClearTimer(StaminaRegenTimer);
	}
	
	GetWorldTimerManager().SetTimer(unusedTimer, this, &ATownDetectiveCharacter::OnStaminaRegenTimerEnd, StaminaRegenDelay);

	StaminaRegenTimer = unusedTimer;

	GEngine->AddOnScreenDebugMessage(0, 55.f, FColor::Red, TEXT("Stamina Regen is now OFF!"));
	
}

void ATownDetectiveCharacter::OnStaminaRegenTimerEnd()
{
	StaminaRegenerating = true;
	GEngine->AddOnScreenDebugMessage(-1, 55.f, FColor::Green, TEXT("Stamina Regen is now ON!"));
}
