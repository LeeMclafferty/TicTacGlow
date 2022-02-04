// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "Kismet/GameplayStatics.h"

#include "TicTacToePlayerController.h"

void UGameplayHUD::Setup()
{
	if(ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{ 
		this->AddToViewport();
		FInputModeGameOnly input_data;
		//input_data.SetWidgetToFocus(this->TakeWidget());
		player_controller->SetInputMode(input_data);
		player_controller->SetShowMouseCursor(true);
	}
}

bool UGameplayHUD::Initialize()
{
	bool success = Super::Initialize();

	if (success)
	{
		
	}

	return success;
}
