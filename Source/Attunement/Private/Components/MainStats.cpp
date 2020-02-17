// Fill out your copyright notice in the Description page of Project Settings.


#include "MainStats.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "Characters/BaseCharacter.h"


// Sets default values for this component's properties
UMainStats::UMainStats()
{
	bReplicates = true;

	//Health defaults
	CurrentHealth = 100.f;
	MaxHealth = 100.f;
	HealthIncreaseRate = 5.f;
	HealthDecreaseRate = 5.f;

	//Stamina Defaults
	CurrentStamina = 100.f;
	MaxStamina = 100.f;
	StaminaIncreaseRate = 5.f;
	StaminaDecreaseRate = 5.f;

	// Mana Defaults
	CurrentGreyMana = 100.f;
	MaxGreyMana = 100.f;
	GreyManaIncreaseRate = 5.f;
	GreyManaDecreaseRate = 5.f;

	HealthRegenRate = 1.f;
	StaminaRegenRate = 1.f;
	GreyManaRegenRate = 1.f;

	BaseCharacter = Cast<ABaseCharacter>(GetOwner());

	//Coin Defaults
	BronzeCoin = 10;
	SilverCoin = 0;
	GoldCoin = 0;

	
}

void UMainStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	// Health Replicated Varibles
	DOREPLIFETIME_CONDITION(UMainStats, CurrentHealth, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UMainStats, MaxHealth, COND_OwnerOnly);

	//Stamina Replicated Varibles
	DOREPLIFETIME_CONDITION(UMainStats, CurrentStamina, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UMainStats, MaxStamina, COND_OwnerOnly);

	//Mana Replicated Varibles
	DOREPLIFETIME_CONDITION(UMainStats, CurrentGreyMana, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UMainStats, MaxGreyMana, COND_OwnerOnly);


	// Coin Varibles
	DOREPLIFETIME(UMainStats, BronzeCoin);
	DOREPLIFETIME(UMainStats, SilverCoin);
	DOREPLIFETIME(UMainStats, GoldCoin);

}

// Called when the game starts
void UMainStats::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		SetTimers();
	}

}


void UMainStats::ControlSprintingTimer(bool IsSprinting)
{
}

void UMainStats::SetCurrentHealth(float Value)
{
}

void UMainStats::SetMaxHealth(float Value)
{
}

void UMainStats::SetHealthRegenRate(float Value)
{
}

void UMainStats::SetCurrentStamina(float Value)
{
}

void UMainStats::SetMaxStamina(float Value)
{
}

void UMainStats::SetStaminaRegenRate(float Value)
{
}

void UMainStats::SetCurrentGreyMana(float Value)
{
}

void UMainStats::SetMaxGreyMana(float Value)
{
}

void UMainStats::SetGreyManaRegenRate(float Value)
{
}

void UMainStats::SetBronzeCoins(float Value)
{
}

void UMainStats::SetSilverCoins(float Value)
{
}

void UMainStats::SetGoldCoins(float Value)
{
}

float UMainStats::GetCurrentStamina()
{
	return 0.0f;
}

float UMainStats::GetMaxStamina()
{
	return 0.0f;
}

float UMainStats::GetStaminaRegenRate()
{
	return 0.0f;
}

float UMainStats::GetCurrentGreyMana()
{
	return 0.0f;
}

float UMainStats::GetMaxGreyMana()
{
	return 0.0f;
}

float UMainStats::GetGreyManaRegenRate()
{
	return 0.0f;
}

float UMainStats::GetBronzeCoins()
{
	return 0.0f;
}

float UMainStats::GetSilverCoins()
{
	return 0.0f;
}

float UMainStats::GetGoldCoins()
{
	return 0.0f;
}

void UMainStats::SetTimers()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this, &UMainStats::HandleIncreaseHealthStats, HealthRegenRate, true);
		GetWorld()->GetTimerManager().SetTimer(StaminaTimerHandle, this, &UMainStats::HandleIncreaseStaminaStats, StaminaRegenRate, true);
		GetWorld()->GetTimerManager().SetTimer(GreyManaTimerHandle, this, &UMainStats::HandleIncreaseGreyManaStats, GreyManaRegenRate, true);
	}
}

void UMainStats::HandleIncreaseHealthStats()
{
	SetCurrentHealth(HealthIncreaseRate);
}

void UMainStats::HandleDecreaseHealthStats()
{
}

void UMainStats::HandleIncreaseStaminaStats()
{
}

void UMainStats::HandleDecreaseStaminaStats()
{
}

void UMainStats::HandleIncreaseGreyManaStats()
{
}

void UMainStats::HandleDecreaseGreyManaStats()
{
}

bool UMainStats::ServerSetCurrentHealth_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetCurrentHealth_Implementation(float Value)
{
}

bool UMainStats::ServerSetMaxHealth_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetMaxHealth_Implementation(float Value)
{
}

bool UMainStats::ServerSetHealthRegen_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetHealthRegen_Implementation(float Value)
{
}

bool UMainStats::ServerSetCurrentStamina_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetCurrentStamina_Implementation(float Value)
{
}

bool UMainStats::ServerSetMaxStamina_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetMaxStamina_Implementation(float Value)
{
}

bool UMainStats::ServerSetStaminaRegen_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetStaminaRegen_Implementation(float Value)
{
}

bool UMainStats::ServerSetCurrentGreyMana_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetCurrentGreyMana_Implementation(float Value)
{
}

bool UMainStats::ServerSetMaxGreyMana_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetMaxGreyMana_Implementation(float Value)
{
}

bool UMainStats::ServerSetGreyManaRegen_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetGreyManaRegen_Implementation(float Value)
{
}

bool UMainStats::ServerControlSprintingTimer_Validate(bool IsSprinting)
{
	return false;
}

void UMainStats::ServerControlSprintingTimer_Implementation(bool IsSprinting)
{
}

bool UMainStats::ServerSetBronzeCoins_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetBronzeCoins_Implementation(float Value)
{
}

bool UMainStats::ServerSetSilverCoins_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetSilverCoins_Implementation(float Value)
{
}

bool UMainStats::ServerSetGoldCoins_Validate(float Value)
{
	return false;
}

void UMainStats::ServerSetGoldCoins_Implementation(float Value)
{
}



