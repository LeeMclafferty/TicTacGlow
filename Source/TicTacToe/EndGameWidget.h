// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(NetMulticast, Reliable)
	void Setup();

	virtual bool Initialize() override;
protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* exit_button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* winner_text;

	UFUNCTION()
	void OnPressExitButton();


private:
	
};
