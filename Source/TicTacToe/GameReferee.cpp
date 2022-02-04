

#include "GameReferee.h"
#include "Kismet/GameplayStatics.h"

#include "PieceSpawner.h"
#include "TicTacToeGameModeBase.h"

AGameReferee::AGameReferee()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameReferee::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameReferee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameReferee::CheckWin()
{
	if(ATicTacToeGameModeBase* gamemode = Cast<ATicTacToeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{ 	
			//X win conditions
		if (spawner01->eowner == OWNER_X && spawner02->eowner == OWNER_X && spawner03->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 1"));

		}
		if (spawner01->eowner == OWNER_X && spawner04->eowner == OWNER_X && spawner07->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 2"));

		}
		if (spawner01->eowner == OWNER_X && spawner05->eowner == OWNER_X && spawner09->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 3"));


		}
		if (spawner02->eowner == OWNER_X && spawner05->eowner == OWNER_X && spawner08->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 4"));

		}
		if (spawner03->eowner == OWNER_X && spawner06->eowner == OWNER_X && spawner09->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 5"));

		}
		if (spawner03->eowner == OWNER_X && spawner05->eowner == OWNER_X && spawner07->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 6"));

		}
		if (spawner04->eowner == OWNER_X && spawner05->eowner == OWNER_X && spawner06->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 7"));

		}
		if (spawner07->eowner == OWNER_X && spawner08->eowner == OWNER_X && spawner09->eowner == OWNER_X)
		{
			gamemode->is_game_over = true;
			gamemode->x_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 8"));

		}

			// O Win Conditions
		if (spawner01->eowner == OWNER_O && spawner02->eowner == OWNER_O && spawner03->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 9"));

		}
		if (spawner01->eowner == OWNER_O && spawner04->eowner == OWNER_O && spawner07->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 10"));

		}
		if (spawner01->eowner == OWNER_O && spawner05->eowner == OWNER_O && spawner09->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 11"));

		}
		if (spawner02->eowner == OWNER_O && spawner05->eowner == OWNER_O && spawner08->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 12"));

		}
		if (spawner03->eowner == OWNER_O && spawner06->eowner == OWNER_O && spawner09->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 13"));

		}
		if (spawner03->eowner == OWNER_O && spawner05->eowner == OWNER_O && spawner07->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 14"));

		}
		if (spawner04->eowner == OWNER_O && spawner05->eowner == OWNER_O && spawner06->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 15"));

		}
		if (spawner07->eowner == OWNER_O && spawner08->eowner == OWNER_O && spawner09->eowner == OWNER_O)
		{
			gamemode->is_game_over = true;
			gamemode->o_is_winner = true;
			UE_LOG(LogTemp, Warning, TEXT("Win Con 16"));

		}

	}
}