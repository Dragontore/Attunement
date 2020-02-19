// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"

#include "Components/BaseStats.h"
#include "Components/MainCharacterMovementComponent.h"



AMainPlayerCharacter::AMainPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UMainCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	BaseStatsComp = CreateDefaultSubobject<UBaseStats>(TEXT("Base Stats Component"));
}

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


}

void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
}

