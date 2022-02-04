// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Kismet//GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "TicTacToeGameModeBase.h"
#include "TicTacToePlayerController.h"
#include "TicTacToeGameInstance.h"

bool UEndGameWidget::Initialize()
{
	bool success = Super::Initialize();

	if (exit_button)
	{
		exit_button->OnPressed.AddDynamic(this, &UEndGameWidget::OnPressExitButton);
	}

	return success;
}

void UEndGameWidget::OnPressExitButton()
{
	if (UTicTacToeGameInstance* game_inst = Cast<UTicTacToeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{ 
			if (player_controller->HasAuthority())
			{
				GetWorld()->ServerTravel("/Game/aa_Maps/MainMenu", false, false);
			}
		}
	}
}

void UEndGameWidget::Setup_Implementation()
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
