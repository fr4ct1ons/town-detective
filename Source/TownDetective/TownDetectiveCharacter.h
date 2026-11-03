// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TownDetectiveCharacter.generated.h"

class ACarriableItem;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class ATownDetectiveCharacter : public ACharacter
{
	GENERATED_BODY()
	
	
public:
	ATownDetectiveCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	////// Components
protected:

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;


	////// Input

	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;
	
	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category="Input")
	void Fire(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category="Input")
	void Reload(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category="Input")
	void Pause(const FInputActionValue& Value);


	////// Stats
	
	/// Health
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	/// Stamina
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxStamina = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool StaminaRegenerating = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaRegenRate = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaRegenDelay = 2.0f;

	FTimerHandle StaminaRegenTimer;
	
	
protected:

	////// Misc

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<ACarriableItem>> StarterCarriables = TArray<TSubclassOf<ACarriableItem>>();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ACarriableItem*> CurrentCarriables = TArray<ACarriableItem*>();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> HandR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ACarriableItem> CurrentCarriable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsTeleporting = false;

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void ResetStaminaRegen();

	void OnStaminaRegenTimerEnd();
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

