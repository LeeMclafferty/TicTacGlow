// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"
#include "TicTacToeGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

AGameBoard::AGameBoard()
{
		//Board is spawned by the gamemode. 
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	gameboard_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Board Mesh"));
	gameboard_mesh->SetupAttachment(RootComponent);

	bReplicates = true;
}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameBoard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameBoard, explosion);
}

