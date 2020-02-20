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

	//Movement Defaluts
	WalkSpeed = 300.0f;
	SprintSpeed = 600.0f;
	
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

	//Movement Replicated Varibles
	DOREPLIFETIME_CONDITION(UMainStats, WalkSpeed, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UMainStats, SprintSpeed, COND_OwnerOnly);


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
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerControlSprintingTimer(IsSprinting);
		return;
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (IsSprinting)
		{
			GetWorld()->GetTimerManager().PauseTimer(StaminaTimerHandle);
		}
		else
		{
			GetWorld()->GetTimerManager().UnPauseTimer(StaminaTimerHandle);
		}
	}
}

float UMainStats::GetCurrentHealth()
{
	return CurrentHealth;
}

float UMainStats::GetMaxHealth()
{
	return MaxHealth;
}

float UMainStats::GetHealthRegenRate()
{
	return HealthRegenRate;
}

void UMainStats::SetCurrentHealth(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetCurrentHealth(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{

		if (CurrentHealth >= MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
		else
		{
			CurrentHealth += Value;
		}
	}
}

void UMainStats::SetMaxHealth(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetMaxHealth(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxHealth += Value;
	}
}

void UMainStats::SetHealthRegenRate(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetHealthRegen(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		HealthRegenRate += Value;
	}
}

void UMainStats::SetCurrentStamina(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetCurrentStamina(Value);
	}
	else if (GetOwnerRole() < ROLE_Authority)
	{
		if (CurrentStamina >= MaxStamina)
		{
			CurrentStamina = MaxStamina;
		}
		else
		{
			CurrentStamina += Value;
		}
	}
}

void UMainStats::SetMaxStamina(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetMaxStamina(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxStamina += Value;
	}
}

void UMainStats::SetStaminaRegenRate(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetStaminaRegen(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		StaminaRegenRate += Value;
	}
}

void UMainStats::SetCurrentGreyMana(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetCurrentGreyMana(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (CurrentGreyMana >= MaxGreyMana)
		{
			CurrentGreyMana = MaxGreyMana;
		}
		else
		{
			CurrentGreyMana += Value;
		}
	}
}

void UMainStats::SetMaxGreyMana(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetMaxGreyMana(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxGreyMana += Value;
	}
}

void UMainStats::SetGreyManaRegenRate(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetGreyManaRegen(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		GreyManaRegenRate += Value;
	}
}

void UMainStats::SetBronzeCoins(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetBronzeCoins(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (GetBronzeCoins() - Value < 0 && GetSilverCoins() > 1)
		{
			SetSilverCoins(-1);
			SetBronzeCoins(+100);
			BronzeCoin += Value;
			return;
		}
		else if (GetBronzeCoins() + Value > 100)
		{
			BronzeCoin += Value;
			BronzeCoin -= 100;
			SetSilverCoins(+1);
			return;
		}
		else if (GetBronzeCoins() - Value < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Enought Money"))
			return;
		}

	}
}

void UMainStats::SetSilverCoins(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetSilverCoins(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (GetSilverCoins() - Value < 0 && GetGoldCoins() > 1)
		{
			SetGoldCoins(-1);
			SilverCoin += 100;
			SilverCoin += Value;
			return;
		}
		else if (GetSilverCoins() + Value > 100)
		{
			SilverCoin += Value;
			SilverCoin -= 100;
			SetGoldCoins(+1);
			return;
		}
		else if (GetSilverCoins() < 1 - Value && GetBronzeCoins() > 100 + Value)
		{
			SetBronzeCoins(+100);
		}
	}
}

void UMainStats::SetGoldCoins(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetGoldCoins(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
	if (GetGoldCoins() - Value < 0)
		{
			SetSilverCoins(+100);
			GoldCoin += Value;
		}
		
	}

}

float UMainStats::GetCurrentStamina()
{
	return CurrentStamina;
}

float UMainStats::GetMaxStamina()
{
	return MaxStamina;
}

float UMainStats::GetStaminaRegenRate()
{
	return StaminaRegenRate;
}

float UMainStats::GetCurrentGreyMana()
{
	return CurrentGreyMana;
}

float UMainStats::GetMaxGreyMana()
{
	return MaxGreyMana;
}

float UMainStats::GetGreyManaRegenRate()
{
	return GreyManaRegenRate;
}

float UMainStats::GetBronzeCoins()
{
	return BronzeCoin;
}

float UMainStats::GetSilverCoins()
{
	return SilverCoin;
}

float UMainStats::GetGoldCoins()
{
	return GoldCoin;
}

float UMainStats::GetWalkSpeed()
{
	return WalkSpeed;
}

float UMainStats::GetSprintSpeed()
{
	return SprintSpeed;
}

void UMainStats::SetWalkSpeed(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetWalkSpeed(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		WalkSpeed += Value;
	}
}

void UMainStats::SetSprintSpeed(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetSprintSpeed(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		SprintSpeed += Value;
	}
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
	SetCurrentHealth(HealthDecreaseRate);
}

void UMainStats::HandleIncreaseStaminaStats()
{
	SetCurrentStamina(StaminaIncreaseRate);
}

void UMainStats::HandleDecreaseStaminaStats()
{
	SetCurrentStamina(StaminaDecreaseRate);
}

void UMainStats::HandleIncreaseGreyManaStats()
{
	SetCurrentGreyMana(GreyManaIncreaseRate);
}

void UMainStats::HandleDecreaseGreyManaStats()
{
	SetCurrentGreyMana(GreyManaDecreaseRate);
}

bool UMainStats::ServerSetCurrentHealth_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetCurrentHealth_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetCurrentHealth(Value);
	}
}

bool UMainStats::ServerSetMaxHealth_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetMaxHealth_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetMaxHealth(Value);
	}
}

bool UMainStats::ServerSetHealthRegen_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetHealthRegen_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetHealthRegenRate(Value);
	}
}

bool UMainStats::ServerSetCurrentStamina_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetCurrentStamina_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetCurrentStamina(Value);
	}
}

bool UMainStats::ServerSetMaxStamina_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetMaxStamina_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetMaxStamina(Value);
	}
}

bool UMainStats::ServerSetStaminaRegen_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetStaminaRegen_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetStaminaRegenRate(Value);
	}
}

bool UMainStats::ServerSetCurrentGreyMana_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetCurrentGreyMana_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetCurrentGreyMana(Value);
	}
}

bool UMainStats::ServerSetMaxGreyMana_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetMaxGreyMana_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetMaxGreyMana(Value);
	}
}

bool UMainStats::ServerSetGreyManaRegen_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetGreyManaRegen_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetGreyManaRegenRate(Value);
	}
}

bool UMainStats::ServerControlSprintingTimer_Validate(bool IsSprinting)
{
	return true;
}

void UMainStats::ServerControlSprintingTimer_Implementation(bool IsSprinting)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		ControlSprintingTimer(IsSprinting);
	}
}

bool UMainStats::ServerSetWalkSpeed_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetWalkSpeed_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetWalkSpeed(Value);
	}
}

bool UMainStats::ServerSetSprintSpeed_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetSprintSpeed_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetSprintSpeed(Value);
	}
}

bool UMainStats::ServerSetBronzeCoins_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetBronzeCoins_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetBronzeCoins(Value);
	}
}

bool UMainStats::ServerSetSilverCoins_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetSilverCoins_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetSilverCoins(Value);
	}
}

bool UMainStats::ServerSetGoldCoins_Validate(float Value)
{
	return true;
}

void UMainStats::ServerSetGoldCoins_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetGoldCoins(Value);
	}
}



