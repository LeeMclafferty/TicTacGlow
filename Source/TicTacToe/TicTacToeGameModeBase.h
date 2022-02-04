// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PieceSpawner.h"
#include "TicTacToeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ATicTacToeGameModeBase();

public:

		//Getter functions
	class AGameBoard* GetGameBoard() { return gameboard; }
	class AGameReferee* GetGameReferee() { return game_referee; }

	UPROPERTY(Replicated)
	bool is_game_over;
	UPROPERTY(Replicated)
	bool is_host_turn;
	UPROPERTY(Replicated)
	bool x_is_winner;
	UPROPERTY(Replicated)
	bool o_is_winner;

	UFUNCTION(NetMulticast, Reliable)
	void DestroyGame();

protected:
		//Override Functions
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

		//Setters
	void SetGameBoard( class AGameBoard* in_gameboard);

	UFUNCTION(NetMulticast, Reliable)
	void SpawnGameBoard();
	void SpawnFloor();
	UFUNCTION(NetMulticast, Reliable)
	void Server_SpawnFloor();


	TArray<AActor*> GameReferees;

	class AGameReferee* game_referee;

private:

	UPROPERTY(Replicated)
	class AGameBoard* gameboard;
	UPROPERTY(Replicated)
	class AFloor* current_floor;

	UPROPERTY()
	TSubclassOf<AGameBoard> gameboard_class;
	UPROPERTY()
	TSubclassOf<AFloor> floor_class;
	
};
