// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStats.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "Characters/BaseCharacter.h"



UBaseStats::UBaseStats()
{
	bReplicates = true;

	// Base State Starting Defaults
	Strength = 1.f;
	Charm = 1.f;
	Perception = 1.f;
	Bravery = 1.f;
	Endurance = 1.f;
	Agility = 1.f;
	Stealth = 1.f;
	Intelligence = 1.f;
	Luck = 1.f;
	UnarmedCombat = 1.f;

}

void UBaseStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required

	// Base Stats Varibles
	DOREPLIFETIME_CONDITION(UBaseStats, Strength, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Charm, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Perception, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Bravery, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Endurance, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Agility, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Stealth, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Intelligence, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, Luck, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBaseStats, UnarmedCombat, COND_OwnerOnly);

}

void UBaseStats::SetStrength(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetStrength(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Strength += Value;
	}
}

void UBaseStats::SetCharm(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetCharm(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Charm += Value;
	}
}

void UBaseStats::SetPerception(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetPerception(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Perception += Value;
	}
}

void UBaseStats::SetBravery(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetBravery(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Bravery += Value;
	}
}

void UBaseStats::SetEndurance(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetEndurance(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Endurance += Value;
	}
}

void UBaseStats::SetAgility(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetAgility(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Agility += Value;
	}
}

void UBaseStats::SetStealth(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetStealth(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Stealth += Value;
	}
}

void UBaseStats::SetIntelligence(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetIntelligence(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Intelligence += Value;
	}
}

void UBaseStats::SetLuck(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetLuck(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Luck += Value;
	}
}

void UBaseStats::SetUnarmedCombat(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerSetUnarmedCombat(Value);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		UnarmedCombat += Value;
	}
}

float UBaseStats::GetStrength()
{
	return Strength;
}

float UBaseStats::GetCharm()
{
	return Charm;
}

float UBaseStats::GetPerception()
{
	return Perception;
}

float UBaseStats::GetBravery()
{
	return Bravery;
}

float UBaseStats::GetEndurance()
{
	return Endurance;
}

float UBaseStats::GetAgility()
{
	return Agility;
}

float UBaseStats::GetStealth()
{
	return Stealth;
}

float UBaseStats::GetIntelligence()
{
	return Intelligence;
}

float UBaseStats::GetLuck()
{
	return Luck;
}

float UBaseStats::GetUnarmedCombat()
{
	return UnarmedCombat;
}

bool UBaseStats::ServerSetStrength_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetStrength_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetStrength(Value);
	}
}

bool UBaseStats::ServerSetCharm_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetCharm_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetCharm(Value);
	}
}

bool UBaseStats::ServerSetPerception_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetPerception_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetPerception(Value);
	}
}

bool UBaseStats::ServerSetBravery_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetBravery_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetBravery(Value);
	}
}

bool UBaseStats::ServerSetEndurance_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetEndurance_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetEndurance(Value);
	}
}

bool UBaseStats::ServerSetAgility_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetAgility_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetAgility(Value);
	}
}

bool UBaseStats::ServerSetStealth_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetStealth_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetStealth(Value);
	}
}

bool UBaseStats::ServerSetIntelligence_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetIntelligence_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetIntelligence(Value);
	}
}

bool UBaseStats::ServerSetLuck_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetLuck_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetLuck(Value);
	}
}

bool UBaseStats::ServerSetUnarmedCombat_Validate(float Value)
{
	return true;
}

void UBaseStats::ServerSetUnarmedCombat_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetUnarmedCombat(Value);
	}
}
