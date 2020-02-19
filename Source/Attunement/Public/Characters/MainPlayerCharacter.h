// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "MainPlayerCharacter.generated.h"

class UBaseStats;

/**
 * 
 */
UCLASS()
class ATTUNEMENT_API AMainPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
		// Non Blueprint Public Functions
	AMainPlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
		// Blueprint Public Functions
public:
		// Non Blueprint Public Varibles
public:
		// Blueprint Public Varibles

			//Added Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBaseStats* BaseStatsComp;

protected:
		// Non Blueprint Protected Functions

		// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
		//Blueprint Protected Functions
protected:
		// Non Blueprint Protected Varibles
protected:
		// Blueprint Protected Varibles
};
