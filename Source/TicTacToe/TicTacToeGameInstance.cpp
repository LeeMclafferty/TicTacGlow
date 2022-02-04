// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacToeGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "GameplayHUD.h"
#include "TicTacToePlayerController.h"
#include "GamePiece.h"
#include "MainMenuWidget.h"
#include "EndGameWidget.h"


UTicTacToeGameInstance::UTicTacToeGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget>game_menu_bp(TEXT("/Game/aa_Blueprints/Widgets/BP_GameplayHUD"));
	if (game_menu_bp.Class != NULL)
	{
		game_menu_class = game_menu_bp.Class;
	}
	ConstructorHelpers::FClassFinder<UUserWidget>main_menu_bp(TEXT("/Game/aa_Blueprints/Widgets/BP_MainMenuWidget"));
	if (main_menu_bp.Class != NULL)
	{
		main_menu_class = main_menu_bp.Class;
		UE_LOG(LogTemp, Warning, TEXT("Main Menu Found"));
	}
	ConstructorHelpers::FClassFinder<AGamePiece> x_bp(TEXT("/Game/aa_Blueprints/Actors/BP_X"));
	if (x_bp.Class != NULL)
	{
		x_game_piece_class = x_bp.Class;
		UE_LOG(LogTemp, Warning, TEXT("X Game Piece Found"));
	}
	ConstructorHelpers::FClassFinder<AGamePiece> o_bp(TEXT("/Game/aa_Blueprints/Actors/BP_O"));
	if (o_bp.Class != NULL)
	{
		o_game_piece_class = o_bp.Class;
		UE_LOG(LogTemp, Warning, TEXT("O Game Piece Found"));

	}
	ConstructorHelpers::FClassFinder<UEndGameWidget> endgame_bp(TEXT("/Game/aa_Blueprints/Widgets/BP_EndGameWidget"));
	if (endgame_bp.Class != NULL)
	{
		endgame_menu_class = endgame_bp.Class;
		UE_LOG(LogTemp, Warning, TEXT("End Game Menu Found"));

	}
}

void UTicTacToeGameInstance::Init()
{
	Super::Init();

	if (game_menu_class != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found game_menu_class: %s"), *game_menu_class->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Class game_menu_class Found"));
	}

}

void UTicTacToeGameInstance::LoadGameMenu()
{
	if(ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{ 
		gameplay_hud = CreateWidget<UGameplayHUD>(this, game_menu_class);

		gameplay_hud->Setup();
	}
}

void UTicTacToeGameInstance::LoadMainMenu()
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		main_menu = CreateWidget<UMainMenuWidget>(this, main_menu_class);

		main_menu->Setup();
	}
}

void UTicTacToeGameInstance::LoadEndGameMenu()
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		endgame_menu = CreateWidget<UEndGameWidget>(this, endgame_menu_class);

		endgame_menu->Setup();
	}
}
