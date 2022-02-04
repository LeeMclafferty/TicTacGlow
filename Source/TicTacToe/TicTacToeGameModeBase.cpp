// Copyright Epic Games, Inc. All Rights Reserved.


#include "TicTacToeGameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

#include "GameBoard.h"
#include "GameReferee.h"
#include "MyNiagaraComponent.h"
#include "Floor.h"

ATicTacToeGameModeBase::ATicTacToeGameModeBase()
{
	ConstructorHelpers::FClassFinder<AActor>gameboard_bp(TEXT("/Game/aa_Blueprints/Actors/BP_GameBoard"));
	if (gameboard_bp.Class != NULL)
	{
		gameboard_class = gameboard_bp.Class;
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Gameboard BP Found")));
	}
	ConstructorHelpers::FClassFinder<AActor>floor_bp(TEXT("/Game/aa_Blueprints/Actors/BP_Floor"));
	if (floor_bp.Class != NULL)
	{
		floor_class = floor_bp.Class;
	}
	
	is_game_over = false;
	is_host_turn = true;
}

void ATicTacToeGameModeBase::BeginPlay()
{
	if(gameboard_class != NULL)
	{ 
		SpawnGameBoard();
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Gameboard Spawned")));
	}
	if (floor_class != NULL)
	{
		Server_SpawnFloor();
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameReferee::StaticClass(), GameReferees);

	game_referee = Cast<AGameReferee>(GameReferees[0]);
}

void ATicTacToeGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATicTacToeGameModeBase, gameboard);
	DOREPLIFETIME(ATicTacToeGameModeBase, is_host_turn);
	DOREPLIFETIME(ATicTacToeGameModeBase, is_game_over);
	DOREPLIFETIME(ATicTacToeGameModeBase, x_is_winner);
	DOREPLIFETIME(ATicTacToeGameModeBase, o_is_winner);
	DOREPLIFETIME(ATicTacToeGameModeBase, current_floor);

}

void ATicTacToeGameModeBase::SetGameBoard(AGameBoard* in_gameboard)
{
	gameboard = in_gameboard;
}

void ATicTacToeGameModeBase::SpawnGameBoard_Implementation()
{
	//To be called in Gamemode Begin play
	AGameBoard* spwned_gameboard;
	FVector location(0.f, 0.f, 20.f);
	FRotator rotation(0.f, 0.f, 0.f);
	FActorSpawnParameters gameboard_params;
	gameboard_params.bNoFail = true;
	//gameboard_params.Owner = Cast<ATicTacToeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	spwned_gameboard = GetWorld()->SpawnActor<AGameBoard>(gameboard_class, location, rotation, gameboard_params);
	SetGameBoard(spwned_gameboard);
}

void ATicTacToeGameModeBase::SpawnFloor()
{
	AFloor* spawned_floor;
	FVector location(0.f, 0.f, 30.f);
	FRotator rotation(0.f, 0.f, 0.f);
	FActorSpawnParameters floor_spawnparams;
	floor_spawnparams.bNoFail = true;
	//gameboard_params.Owner = Cast<ATicTacToeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	spawned_floor = GetWorld()->SpawnActor<AFloor>(floor_class, location, rotation, floor_spawnparams);

	current_floor = spawned_floor;
}

void ATicTacToeGameModeBase::Server_SpawnFloor_Implementation()
{
	//To be called in Gamemode Begin play
	AFloor* spawned_floor;
	FVector location(0.f, 0.f, 30.f);
	FRotator rotation(0.f, 0.f, 0.f);
	FActorSpawnParameters floor_spawnparams;
	floor_spawnparams.bNoFail = true;
	//gameboard_params.Owner = Cast<ATicTacToeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	spawned_floor = GetWorld()->SpawnActor<AFloor>(floor_class, location, rotation, floor_spawnparams);

	current_floor = spawned_floor;
}

void ATicTacToeGameModeBase::DestroyGame_Implementation()
{
	gameboard->SetHidden(true);
	current_floor->DisableMesh();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), GetGameBoard()->explosion, FVector(0 , 0 , -1000.f));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("should Show on all")));
}

