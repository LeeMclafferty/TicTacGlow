// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <TicTacToe/PieceSpawner.h>
#include "TicTacToePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToePlayerController : public APlayerController
{
	GENERATED_BODY()

	ATicTacToePlayerController();

public:
	UFUNCTION()
	void TraceUnderCursor();
	UFUNCTION()
	void SpawnGamePiece(FVector location, APieceSpawner* other_actor);

	bool GetIsHost() { return is_host; }
	void SetIsHost(bool in_value);

	UPROPERTY(Replicated)
	TSubclassOf<class AGamePiece> current_gamepiece_class;

	UPROPERTY()
	bool is_x_piece;

protected:

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SpawnGamePiece(FVector location, APieceSpawner* other_actor);

	UFUNCTION(Server,Reliable,WithValidation)
	void Server_SetOwner(class APieceSpawner* in_spawner);

	UFUNCTION(Server, Reliable)
	void Server_CheckWin();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Server_EndGame();

	UFUNCTION()
	void Client_LoadEndGameUI();

	bool is_host;

	UPROPERTY()
	TSubclassOf<class AGamePiece> x_game_piece_class;

	UPROPERTY()
	TSubclassOf<class AGamePiece> o_game_piece_class;

	
	
};
