// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePiece.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AGamePiece::AGamePiece()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	gamepiece_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Piece Mesh"));
	gamepiece_mesh->SetupAttachment(RootComponent);

	bReplicates = true;
	
}

void AGamePiece::BeginPlay()
{
	Super::BeginPlay();

	//Spawn in air above selected slot
	// slam down to slot and play vfx
	
}

void AGamePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

