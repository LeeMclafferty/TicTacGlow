// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/EditableTextBox.h"

#include "TicTacToePlayerController.h"
#include "TicTacToeGameInstance.h"

bool UMainMenuWidget::Initialize()
{
	bool success = Super::Initialize();

	if (host_button)
	{
		host_button->OnPressed.AddDynamic(this, &UMainMenuWidget::OnHostButtonPresed);
	}
	if (join_button)
	{
		join_button->OnPressed.AddDynamic(this, &UMainMenuWidget::OnJoinButtonPresed);

	}
	if (quit_button)
	{
		quit_button->OnPressed.AddDynamic(this, &UMainMenuWidget::OnQuitButtonPresed);

	}
	if (host_menu_back)
	{
		host_menu_back->OnPressed.AddDynamic(this, &UMainMenuWidget::OnBackButtonPresed);
	}
	if (start_hosting_button)
	{
		start_hosting_button->OnPressed.AddDynamic(this, &UMainMenuWidget::OnStartHostingButtonPressed);
	}
	if (join_ip_button)
	{
		join_ip_button->OnPressed.AddDynamic(this, &UMainMenuWidget::OnJoinIPButtonPressed);
	}
	if (join_menu_back)
	{
		join_menu_back->OnPressed.AddDynamic(this, &UMainMenuWidget::OnBackButtonPresed);
	}
	return success;
}

void UMainMenuWidget::Setup()
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		this->AddToViewport();
		FInputModeUIOnly input_data;
		//input_data.SetWidgetToFocus(this->TakeWidget());
		player_controller->SetInputMode(input_data);
		player_controller->SetShowMouseCursor(true);
	}
}

void UMainMenuWidget::OnHostButtonPresed()
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{ 
		if (UTicTacToeGameInstance* game_inst = Cast<UTicTacToeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			player_controller->current_gamepiece_class = game_inst->x_game_piece_class;
			player_controller->is_x_piece = true;
			menu_switcher->SetActiveWidget(host_menu);
		}
	}
}

void UMainMenuWidget::OnJoinButtonPresed()
{
	menu_switcher->SetActiveWidget(join_menu);
}

void UMainMenuWidget::OnQuitButtonPresed()
{

	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), player_controller, EQuitPreference::Quit, false);
	}
}

void UMainMenuWidget::OnBackButtonPresed()
{
	menu_switcher->SetActiveWidget(main_menu);
}

void UMainMenuWidget::OnStartHostingButtonPressed()
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if(GetWorld() != NULL)
		{ 
			player_controller->SetIsHost(true);
			player_controller->is_x_piece = false;
			GetWorld()->ServerTravel("/Game/aa_Maps/GameMap?listen");
		}
	}
}

void UMainMenuWidget::OnJoinIPButtonPressed()
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{ 
		if(UTicTacToeGameInstance* game_inst = Cast<UTicTacToeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			player_controller->current_gamepiece_class = game_inst->o_game_piece_class;
			Join(ip_text_box->GetText().ToString());
		}
	}
}

void UMainMenuWidget::Join(FString in_text)
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (GetWorld() != NULL)
		{ 
			player_controller->SetIsHost(false);
			player_controller->ClientTravel(in_text, ETravelType::TRAVEL_Absolute);	
		}
	}
}
