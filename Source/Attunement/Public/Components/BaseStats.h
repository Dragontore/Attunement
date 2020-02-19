// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MainStats.h"
#include "BaseStats.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class ATTUNEMENT_API UBaseStats : public UMainStats
{
	GENERATED_BODY()


public:
		// Non Blueprint Public Functions
	UBaseStats();

	//Non Server Increase Base Stat Function
	void SetStrength(float Value);
	void SetCharm(float Value);
	void SetPerception(float Value);
	void SetBravery(float Value);
	void SetEndurance(float Value);
	void SetAgility(float Value);
	void SetStealth(float Value);
	void SetIntelligence(float Value);
	void SetLuck(float Value);
	void SetUnarmedCombat(float Value);

public:
		// Blueprint Public Functions

		// Base Stats Getter Functions
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetStrength();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetCharm();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetPerception();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetBravery();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetEndurance();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetAgility();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetStealth();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetIntelligence();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetLuck();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetUnarmedCombat();
public:
		// Non Blueprint Public Varibles
public:
		// Blueprint Public Varibles
protected:
		// Non Blueprint Protected Functions
protected:
		// Blueprint Protected Functions

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetStrength(float Value);
	bool ServerSetStrength_Validate(float Value);
	void ServerSetStrength_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetCharm(float Value);
	bool ServerSetCharm_Validate(float Value);
	void ServerSetCharm_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetPerception(float Value);
	bool ServerSetPerception_Validate(float Value);
	void ServerSetPerception_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetBravery(float Value);
	bool ServerSetBravery_Validate(float Value);
	void ServerSetBravery_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetEndurance(float Value);
	bool ServerSetEndurance_Validate(float Value);
	void ServerSetEndurance_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetAgility(float Value);
	bool ServerSetAgility_Validate(float Value);
	void ServerSetAgility_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetStealth(float Value);
	bool ServerSetStealth_Validate(float Value);
	void ServerSetStealth_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetIntelligence(float Value);
	bool ServerSetIntelligence_Validate(float Value);
	void ServerSetIntelligence_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetLuck(float Value);
	bool ServerSetLuck_Validate(float Value);
	void ServerSetLuck_Implementation(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetUnarmedCombat(float Value);
	bool ServerSetUnarmedCombat_Validate(float Value);
	void ServerSetUnarmedCombat_Implementation(float Value);

protected:
		// Non Blueprint Protected Varibles

	ABaseCharacter* BaseCharacter;

protected:
		// Blueprint Protected Varibles

		//Base Stats

	UPROPERTY(Replicated, VisibleAnywhere)
	float Strength;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Charm;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Perception;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Bravery;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Endurance;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Agility;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Stealth;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Intelligence;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Luck;

	UPROPERTY(Replicated, VisibleAnywhere)
	float UnarmedCombat;
};
