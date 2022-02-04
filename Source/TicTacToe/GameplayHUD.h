// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UGameplayHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void Setup();

protected:
	
	virtual bool Initialize() override;
private:
};
