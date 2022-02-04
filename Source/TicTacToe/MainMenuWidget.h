// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;
	void Setup();

	UPROPERTY(meta = (BindWidget))
	class UButton* host_button;

	UPROPERTY(meta = (BindWidget))
	class UWidget* host_menu;

	UPROPERTY(meta = (BindWidget))
	class UButton* join_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit_button;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* menu_switcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* host_menu_back;

	UPROPERTY(meta = (BindWidget))
	class UWidget* main_menu;

	UPROPERTY(meta = (BindWidget))
	class UButton* start_hosting_button;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* ip_text_box;

	UPROPERTY(meta = (BindWidget))
	class UButton* join_ip_button;

	UPROPERTY(meta = (BindWidget))
	class UWidget* join_menu;

	UPROPERTY(meta = (BindWidget))
	class UButton* join_menu_back;


protected:

	UFUNCTION()
	void OnHostButtonPresed();

	UFUNCTION()
	void OnJoinButtonPresed();

	UFUNCTION()
	void OnQuitButtonPresed();

	UFUNCTION()
	void OnBackButtonPresed();

	UFUNCTION()
	void OnStartHostingButtonPressed();

	UFUNCTION()
	void OnJoinIPButtonPressed();

	UFUNCTION()
	void Join(FString in_text);


private:
	
};
