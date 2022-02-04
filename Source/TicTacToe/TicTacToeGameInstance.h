// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TicTacToeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UTicTacToeGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UTicTacToeGameInstance();
	virtual void Init() override;
	
public:

	UFUNCTION(BlueprintCallable, Category = "Menus")
	void LoadGameMenu();

	UFUNCTION(BlueprintCallable, Category = "Menus")
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Menus")
	void LoadEndGameMenu();

	UPROPERTY()
	TSubclassOf<class AGamePiece> x_game_piece_class;

	UPROPERTY()
	TSubclassOf<class AGamePiece> o_game_piece_class;

	UPROPERTY()
	FString game_winner;

protected:

	UPROPERTY()
	class UGameplayHUD* gameplay_hud;
	UPROPERTY()
	class UMainMenuWidget* main_menu;
	UPROPERTY()
	class UEndGameWidget* endgame_menu;

private:

	UPROPERTY()
	TSubclassOf<UUserWidget> game_menu_class;

	UPROPERTY()
	TSubclassOf<UUserWidget> main_menu_class;

	UPROPERTY()
	TSubclassOf<UUserWidget> endgame_menu_class;

};
