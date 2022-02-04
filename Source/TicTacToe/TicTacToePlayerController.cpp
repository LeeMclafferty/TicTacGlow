// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "PieceSpawner.h"
#include "GamePiece.h"
#include "TicTacToePawn.h"
#include "TicTacToeGameModeBase.h"
#include "GameReferee.h"
#include "TicTacToeGameInstance.h"

ATicTacToePlayerController::ATicTacToePlayerController()
{
	bReplicates = true;

}

void ATicTacToePlayerController::BeginPlay()
{
	if (UTicTacToeGameInstance* game_inst = Cast<UTicTacToeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		x_game_piece_class = game_inst->x_game_piece_class;
		o_game_piece_class = game_inst->o_game_piece_class;
	}
	if(HasAuthority())
		current_gamepiece_class = x_game_piece_class;
	if(!HasAuthority())
		current_gamepiece_class = o_game_piece_class;
}

void ATicTacToePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATicTacToePlayerController, current_gamepiece_class);
}

void ATicTacToePlayerController::TraceUnderCursor()
{
	FHitResult out_hit;
		//Make sure to use the right trace channel you idiot.
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true,  out_hit);
	
	if (APieceSpawner* spawner = Cast<APieceSpawner>(out_hit.Actor))
	{
		if(ATicTacToePawn* pawn = Cast<ATicTacToePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
		{ 
				FVector spawn_loc = spawner->GetActorLocation();
				SpawnGamePiece(spawn_loc, spawner);
				if (HasAuthority())
				{
					spawner->eowner = OWNER_X;
				}
				if (!HasAuthority())
				{
					Server_SetOwner(spawner);
				}
			Server_CheckWin();
		}
	}
}

void ATicTacToePlayerController::SpawnGamePiece(FVector location, APieceSpawner* other_actor)
{
	if (ATicTacToePawn* pawn = Cast<ATicTacToePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{ 
			//If you are the server spawn the piece
		if (ATicTacToeGameModeBase* gamemode = Cast<ATicTacToeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			if(HasAuthority() && gamemode->is_host_turn)
			{
				if (!other_actor->has_been_triggered)
				{
					AGamePiece* spawned_piece;
					FVector spawn_location = location;
					FRotator rotation(0.f, 0.f, 0.f);
					FVector scale(0.f, 0.f, 0.f);
					FActorSpawnParameters gamepiece_spawnparams;
					gamepiece_spawnparams.bNoFail = true;
				
					spawned_piece = GetWorld()->SpawnActor<AGamePiece>(x_game_piece_class, location, rotation, gamepiece_spawnparams);

					//pawn->SetGamePiece(spawned_piece);
					other_actor->SetHasBeenTriggered(true);
					
					if (gamemode->is_game_over)
					{
						GEngine->AddOnScreenDebugMessage(1, 5, FColor::Purple, FString::Printf(TEXT("current game over")));
						GEngine->AddOnScreenDebugMessage(1, 5, FColor::Purple, FString::Printf(TEXT("X is winnger: %i"), gamemode->x_is_winner));
					}
						gamemode->is_host_turn = false;
				}
			}
			
		}
		
		//If you are not call the Server RPC 
		if (!HasAuthority())
		{
			Server_SpawnGamePiece(location, other_actor);
		}
	}
}

void ATicTacToePlayerController::Server_SpawnGamePiece_Implementation(FVector location, APieceSpawner* other_actor)
{
	if (ATicTacToeGameModeBase* gamemode = Cast<ATicTacToeGameModeBase>(GetWorld()->GetAuthGameMode()))
	{ 
	//SpawnGamePiece(location, other_actor);
		if (HasAuthority() && !gamemode->is_host_turn)
		{
			if (!other_actor->has_been_triggered)
			{
				AGamePiece* spawned_piece;
				FVector spawn_location = location;
				FRotator rotation(0.f, 0.f, 0.f);
				FVector scale(0.f, 0.f, 0.f);
				FActorSpawnParameters gamepiece_spawnparams;
				gamepiece_spawnparams.bNoFail = true;

				spawned_piece = GetWorld()->SpawnActor<AGamePiece>(o_game_piece_class, location, rotation, gamepiece_spawnparams);

				//pawn->SetGamePiece(spawned_piece);
				other_actor->SetHasBeenTriggered(true);
				
				gamemode->is_host_turn =true;
			}
		}
	}

}


void ATicTacToePlayerController::Server_SetOwner_Implementation(class APieceSpawner* in_spawner)
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Purple, FString::Printf(TEXT("Client")));

	in_spawner->eowner = OWNER_O;
}

bool ATicTacToePlayerController::Server_SetOwner_Validate(class APieceSpawner* in_spawner)
{
	return true;
}

void ATicTacToePlayerController::Server_CheckWin_Implementation()
{
	if (ATicTacToeGameModeBase* gamemode = Cast<ATicTacToeGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		gamemode->GetGameReferee()->CheckWin();

		if (gamemode->is_game_over)
		{
			Server_EndGame();
		}
	}
}

void ATicTacToePlayerController::SetIsHost(bool in_value)
{
	is_host = in_value;
}


bool ATicTacToePlayerController::Server_SpawnGamePiece_Validate(FVector location, APieceSpawner* other_actor)
{
	return true;
}

void ATicTacToePlayerController::Server_EndGame_Implementation()
{
	if (ATicTacToeGameModeBase* gamemode = Cast<ATicTacToeGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		if (UTicTacToeGameInstance* game_inst = Cast<UTicTacToeGameInstance>(GetWorld()->GetGameInstance()))
		{
			if (gamemode->x_is_winner)
			{
				game_inst->game_winner = "Player 1 Wins!";
			}
			if (gamemode->o_is_winner)
			{
				game_inst->game_winner = "Player 2 Wins!";
			}
		
			gamemode->DestroyGame();
			Client_LoadEndGameUI();
			game_inst->LoadEndGameMenu();
		}
	}
}

bool ATicTacToePlayerController::Server_EndGame_Validate()
{

 return true;

}

void ATicTacToePlayerController::Client_LoadEndGameUI()
{
	if (UTicTacToeGameInstance* game_inst = Cast<UTicTacToeGameInstance>(GetWorld()->GetGameInstance()))
	{
		game_inst->LoadEndGameMenu();
	}
}

