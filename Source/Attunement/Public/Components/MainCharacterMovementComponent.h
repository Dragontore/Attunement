// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacterMovementComponent.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class ATTUNEMENT_API UMainCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

	friend class FSavedMove_ExtendedMyMovement;

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	class FSavedMove_Attunement : public FSavedMove_Character
		{
		public:



			typedef FSavedMove_Character Super;

			virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;
			virtual void Clear() override;
			virtual uint8 GetCompressedFlags() const override;
			virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
			virtual void PrepMoveFor(ACharacter* Character) override;

			//Walk Speed Update
			uint8 bSavedRequestMaxWalkSpeedChange : 1;

			//Dodge
			FVector SavedMoveDirection;
			uint8 bSavedWantsToDodge : 1;
		};
	
	class FNetworkPredictionData_Client_Attunement : public FNetworkPredictionData_Client_Character
	{
		public:
			FNetworkPredictionData_Client_Attunement(const UCharacterMovementComponent& ClientMovement);

			typedef FNetworkPredictionData_Client_Character Super;

			virtual FSavedMovePtr AllocateNewMove() override;
	};

public:
	//Non Blueprint Public Functions

	virtual bool HandlePendingLaunch()override;
	
	void OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity);

public:
	// Blueprint Public Functions

	UFUNCTION(Unreliable, Server, WithValidation)
	void Server_SetMaxWalkSpeed(const float NewMaxWalkSpeed);

	//Set Max Walk Speed(Called for the Owning Client)
	UFUNCTION(BlueprintCallable, Category = "Max Walk Speed")
	void SetMaxWalkSpeed(float NewMaxWalkSpeed);

	//Dodge
	UFUNCTION(Unreliable, Server, WithValidation)
	void Server_MoveDirection(const FVector& MoveDir);

	//Trigger the Dodge Ability (Called from Owning Cilent)
	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void Dodge();

public:
	// Non Blueprint Public Varibles

	//Set Max Walk Speed
	uint8 bRequestMaxWalkSpeedChange : 1;
	float CharacterNewMaxWalkSpeed;

	//Dodge
	FVector MoveDirection;
	uint8 bWantsToDodge : 1;

public:
	// Blueprint Public Varibles

	//Dodge
	UPROPERTY(EditAnywhere, Category = "Dodge")
	float DodgeStrength;


};
