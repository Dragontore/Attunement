// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"

#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerStart.h"

// Sets default values
ABaseRoom::ABaseRoom()
{
	bReplicates = true;

	PlayerStart = CreateDefaultSubobject<APlayerStart>("Player Start");

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Floor Mesh");
	RootComponent = FloorMesh;

	RoofMesh = CreateDefaultSubobject<UStaticMeshComponent>("Roof Mesh");
	RoofMesh->SetupAttachment(RootComponent);

	Wall1Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Wall 1 Mesh");
	Wall1Mesh->SetupAttachment(RootComponent);

	Wall2Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Wall 2 Mesh");
	Wall2Mesh->SetupAttachment(RootComponent);

	Wall3Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Wall 3 Mesh");
	Wall3Mesh->SetupAttachment(RootComponent);

	Wall4Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Wall 4 Mesh");
	Wall4Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

void  ABaseRoom::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	// 

	DOREPLIFETIME(ABaseRoom, FloorMesh);
	DOREPLIFETIME(ABaseRoom, RoofMesh);
	DOREPLIFETIME(ABaseRoom, Wall1Mesh);
	DOREPLIFETIME(ABaseRoom, Wall2Mesh);
	DOREPLIFETIME(ABaseRoom, Wall3Mesh);
	DOREPLIFETIME(ABaseRoom, Wall4Mesh);

}



