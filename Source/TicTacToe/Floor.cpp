// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Sceen Root"));

	floor_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Mesh"));
	floor_mesh->SetupAttachment(RootComponent);

	floor_mesh->bHiddenInGame = true;
	floor_mesh->SetCollisionProfileName("BlockAll");

	bReplicates = true;

}

void AFloor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFloor, floor_mesh);
}

void AFloor::DisableMesh_Implementation()
{
	floor_mesh->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

