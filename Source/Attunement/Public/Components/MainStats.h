// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainStats.generated.h"


class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATTUNEMENT_API UMainStats : public UActorComponent
{
	GENERATED_BODY()

public:	

		//Non Blueprint Public functions
	// Sets default values for this component's properties
	UMainStats();

	//Character Functions

	void ControlSprintingTimer(bool IsSprinting);

public:
		//Blueprint Public Functions

		// Non Server Health Function
	UFUNCTION(BlueprintCallable, Category = "Health Function")
	void SetCurrentHealth(float Value);
	UFUNCTION(BlueprintCallable, Category = "Health Function")
	void SetMaxHealth(float Value);
	UFUNCTION(BlueprintCallable, Category = "Health Function")
	void SetHealthRegenRate(float Value);

	// Non Server Stamina Function
	UFUNCTION(BlueprintCallable, Category = "Stamina Function")
	void SetCurrentStamina(float Value);
	UFUNCTION(BlueprintCallable, Category = "Stamina Function")
	void SetMaxStamina(float Value);
	UFUNCTION(BlueprintCallable, Category = "Stamina Function")
	void SetStaminaRegenRate(float Value);

	// Non Server Mana Function
	UFUNCTION(BlueprintCallable, Category = "Grey Mana Function")
	void SetCurrentGreyMana(float Value);
	UFUNCTION(BlueprintCallable, Category = "Grey Mana Function")
	void SetMaxGreyMana(float Value);
	UFUNCTION(BlueprintCallable, Category = "Grey Mana Function")
	void SetGreyManaRegenRate(float Value);

	// Non Server Coin Function
	UFUNCTION(BlueprintCallable, Category = "Coin Function")
	void SetBronzeCoins(float Value);
	UFUNCTION(BlueprintCallable, Category = "Coin Function")
	void SetSilverCoins(float Value);
	UFUNCTION(BlueprintCallable, Category = "Coin Function")
	void SetGoldCoins(float Value);

	// Stamina Getter Function
	UFUNCTION(BlueprintCallable, Category = "StaminaGetter")
	float GetCurrentStamina();
	UFUNCTION(BlueprintCallable, Category = "Stamina Getter")
	float GetMaxStamina();
	UFUNCTION(BlueprintCallable, Category = "Stamina Getter")
	float GetStaminaRegenRate();

	//Mana Getter Function
	UFUNCTION(BlueprintCallable, Category = "Mana Getter")
	float GetCurrentGreyMana();
	UFUNCTION(BlueprintCallable, Category = "Mana Getter")
	float GetMaxGreyMana();
	UFUNCTION(BlueprintCallable, Category = "Mana Getter")
	float GetGreyManaRegenRate();

	//Coin Getter Function
	UFUNCTION(BlueprintCallable, Category = "Coin Getter")
	float GetBronzeCoins();
	UFUNCTION(BlueprintCallable, Category = "Coin Getter")
	float GetSilverCoins();
	UFUNCTION(BlueprintCallable, Category = "Coin Getter")
	float GetGoldCoins();



public:
		//Non Blueprint Public Varibles

public:
		// Blueprint Public Varibles

protected:
		// Non Blueprint Protected Functions
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetTimers();

	//Handles the Health Stats regen/Degen
	void HandleIncreaseHealthStats();
	void HandleDecreaseHealthStats();

	//Handles the Stamina Stats Regen/Degen
	void HandleIncreaseStaminaStats();
	void HandleDecreaseStaminaStats();

	//Handle the Mana Stats Regen/Degen
	void HandleIncreaseGreyManaStats();
	void HandleDecreaseGreyManaStats();

protected:
		// Blueprint Protected Functions

		// Health Server Functions
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetCurrentHealth(float Value);
	bool ServerSetCurrentHealth_Validate(float Value);
	void ServerSetCurrentHealth_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetMaxHealth(float Value);
	bool ServerSetMaxHealth_Validate(float Value);
	void ServerSetMaxHealth_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetHealthRegen(float Value);
	bool ServerSetHealthRegen_Validate(float Value);
	void ServerSetHealthRegen_Implementation(float Value);

	//Stamina Server Functions
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetCurrentStamina(float Value);
	bool ServerSetCurrentStamina_Validate(float Value);
	void ServerSetCurrentStamina_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetMaxStamina(float Value);
	bool ServerSetMaxStamina_Validate(float Value);
	void ServerSetMaxStamina_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetStaminaRegen(float Value);
	bool ServerSetStaminaRegen_Validate(float Value);
	void ServerSetStaminaRegen_Implementation(float Value);

	//Mana Server Function
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetCurrentGreyMana(float Value);
	bool ServerSetCurrentGreyMana_Validate(float Value);
	void ServerSetCurrentGreyMana_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetMaxGreyMana(float Value);
	bool ServerSetMaxGreyMana_Validate(float Value);
	void ServerSetMaxGreyMana_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetGreyManaRegen(float Value);
	bool ServerSetGreyManaRegen_Validate(float Value);
	void ServerSetGreyManaRegen_Implementation(float Value);

	// Server Sprint Function

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerControlSprintingTimer(bool IsSprinting);
	bool ServerControlSprintingTimer_Validate(bool IsSprinting);
	void ServerControlSprintingTimer_Implementation(bool IsSprinting);

	//Server Coin Functions

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetBronzeCoins(float Value);
	bool ServerSetBronzeCoins_Validate(float Value);
	void ServerSetBronzeCoins_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetSilverCoins(float Value);
	bool ServerSetSilverCoins_Validate(float Value);
	void ServerSetSilverCoins_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetGoldCoins(float Value);
	bool ServerSetGoldCoins_Validate(float Value);
	void ServerSetGoldCoins_Implementation(float Value);
protected:
		// Non Blueprint Protected Varibles

	ABaseCharacter* BaseCharacter;

	FTimerHandle HealthTimerHandle;
	FTimerHandle StaminaTimerHandle;
	FTimerHandle GreyManaTimerHandle;

	float HealthIncreaseRate;
	float HealthDecreaseRate;

	float StaminaIncreaseRate;
	float StaminaDecreaseRate;

	float GreyManaIncreaseRate;
	float GreyManaDecreaseRate;

protected:
		// Blueprint Protected Varibles

		// Health Varibles
	UPROPERTY(Replicated)
	float CurrentHealth;

	UPROPERTY(Replicated)
	float MaxHealth;

	//Stamina Varibles
	UPROPERTY(Replicated)
	float CurrentStamina;

	UPROPERTY(Replicated)
	float MaxStamina;

	//Mana Varibles
	UPROPERTY(Replicated)
	float CurrentGreyMana;

	UPROPERTY(Replicated)
	float MaxGreyMana;

	//Regenratiion rate for Health stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float HealthRegenRate;

	//Regenratiion rate for Health stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float StaminaRegenRate;

	//Regenratiion rate for Health stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float GreyManaRegenRate;

	UPROPERTY(Replicated)
	int BronzeCoin;

	UPROPERTY(Replicated)
	int SilverCoin;

	UPROPERTY(Replicated)
	int GoldCoin;
		
};
