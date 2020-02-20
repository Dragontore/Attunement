// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRoom.generated.h"

class UStaticMeshComponent;
class APlayerStart;

UCLASS()
class ATTUNEMENT_API ABaseRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Non Blueprint Public Functions
	// Sets default values for this actor's properties
	ABaseRoom();

public:
	// Blueprint Public Functions
public:
	//  Non Blueprint Public Varibles
public:
	// Blueprint Public Varibles
protected:
	// Non Blueprint Protected Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Blueprint Protected Functions
protected:
	// Non Blueprint Protected Varibles
protected:
	// Blueprint Protected Varibles
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* RoofMesh;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* Wall1Mesh;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* Wall2Mesh;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* Wall3Mesh;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* Wall4Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	APlayerStart* PlayerStart;


};
