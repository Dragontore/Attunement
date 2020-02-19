// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterMovementComponent.h"

#include "UObject/UObjectGlobals.h"

#include "Characters/BaseCharacter.h"
#include "Characters/MainPlayerCharacter.h"

UMainCharacterMovementComponent::UMainCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DodgeStrength = 10000.f;
}

void UMainCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	bRequestMaxWalkSpeedChange = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	bWantsToDodge = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
}

FNetworkPredictionData_Client* UMainCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != NULL);
	check(PawnOwner->Role < ROLE_Authority);

	if (!ClientPredictionData)
	{
		UMainCharacterMovementComponent* MutableThis = const_cast<UMainCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Attunement(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}
	return ClientPredictionData;
}

bool UMainCharacterMovementComponent::HandlePendingLaunch()
{
	if (!PendingLaunchVelocity.IsZero() && HasValidData())
	{
		Velocity = PendingLaunchVelocity;

		PendingLaunchVelocity = FVector::ZeroVector;
		bForceNextFloorCheck = true;
		return true;
	}
	return false;
}

void UMainCharacterMovementComponent::OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaTime, OldLocation, OldVelocity);

	if (!CharacterOwner)
	{
		return;
	}

	if (bRequestMaxWalkSpeedChange)
	{
		bRequestMaxWalkSpeedChange = false;
		MaxWalkSpeed = CharacterNewMaxWalkSpeed;
	}

	//Dodge
	if (bWantsToDodge)
	{
		bWantsToDodge = false;

		// TODO put in check if character is falling
		if(IsMovingOnGround())
		{
			MoveDirection.Normalize();
			FVector DodgeVelocity = MoveDirection * DodgeStrength;
			//Set Z Component ro Zreo so we Dont go Up
			DodgeVelocity.Z = 0.0f;

			Launch(DodgeVelocity);
		}
	}
}

void UMainCharacterMovementComponent::SetMaxWalkSpeed(float NewMaxWalkSpeed)
{
	if (PawnOwner->IsLocallyControlled())
	{
		CharacterNewMaxWalkSpeed = NewMaxWalkSpeed;
		Server_SetMaxWalkSpeed(NewMaxWalkSpeed);
	}
	bRequestMaxWalkSpeedChange = true;
}

void UMainCharacterMovementComponent::Dodge()
{
	if (PawnOwner->IsLocallyControlled())
	{
		MoveDirection = PawnOwner->GetLastMovementInputVector();
		Server_MoveDirection(MoveDirection);
	}
	bWantsToDodge = true;
}

bool UMainCharacterMovementComponent::Server_MoveDirection_Validate(const FVector& MoveDir)
{
	return true;
}

void UMainCharacterMovementComponent::Server_MoveDirection_Implementation(const FVector& MoveDir)
{
	//TODO Turn off Ground Friction and Reset Dodge Strength.
	MoveDirection = MoveDir;
	//TODO once move complete to ground friction on.
}

bool UMainCharacterMovementComponent::Server_SetMaxWalkSpeed_Validate(const float NewMaxWalkSpeed)
{
	if (NewMaxWalkSpeed < 0.f || NewMaxWalkSpeed > 2000.f) // Change top speed as required.
	
		return false;
	else
		return true;
	
}

void UMainCharacterMovementComponent::Server_SetMaxWalkSpeed_Implementation(const float NewMaxWalkSpeed)
{
	CharacterNewMaxWalkSpeed = NewMaxWalkSpeed;
}

bool UMainCharacterMovementComponent::FSavedMove_Attunement::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
	// TODO Possiblility to Combine with each other.
	//Set which moves can be combined together. this will depen on the bit flags that are used.
	if (bSavedRequestMaxWalkSpeedChange != ((FSavedMove_Attunement*)&NewMove)->bSavedRequestMaxWalkSpeedChange)
	{
		return false;
	}
	if (bSavedWantsToDodge != ((FSavedMove_Attunement*)&NewMove)->bSavedWantsToDodge)
	{
		return false;
	}
	if (SavedMoveDirection != ((FSavedMove_Attunement*)&NewMove)->SavedMoveDirection)
	{
		return false;
	}
	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void UMainCharacterMovementComponent::FSavedMove_Attunement::Clear()
{
	Super::Clear();

	bSavedRequestMaxWalkSpeedChange = false;
	bSavedWantsToDodge = false;
	SavedMoveDirection = FVector::ZeroVector;
}

uint8 UMainCharacterMovementComponent::FSavedMove_Attunement::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (bSavedRequestMaxWalkSpeedChange)
	{
		Result |= FLAG_Custom_0;
	}

	if (bSavedWantsToDodge)
	{
		Result |= FLAG_Custom_1;
	}
	return Result;
}

void UMainCharacterMovementComponent::FSavedMove_Attunement::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UMainCharacterMovementComponent* CharacterMovement = Cast<UMainCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		bSavedRequestMaxWalkSpeedChange = CharacterMovement->bRequestMaxWalkSpeedChange;
		bSavedWantsToDodge = CharacterMovement->bWantsToDodge;
		SavedMoveDirection = CharacterMovement->MoveDirection;
	}
}

void UMainCharacterMovementComponent::FSavedMove_Attunement::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	UMainCharacterMovementComponent* CharacterMovement = Cast<UMainCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		CharacterMovement->MoveDirection = SavedMoveDirection;
	}
}

UMainCharacterMovementComponent::FNetworkPredictionData_Client_Attunement::FNetworkPredictionData_Client_Attunement(const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{

}

FSavedMovePtr UMainCharacterMovementComponent::FNetworkPredictionData_Client_Attunement::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_Attunement());
}
