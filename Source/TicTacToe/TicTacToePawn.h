// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TicTacToePawn.generated.h"

UCLASS()
class TICTACTOE_API ATicTacToePawn : public APawn
{
	GENERATED_BODY()

public:
	ATicTacToePawn();

	virtual void Tick(float DeltaTime) override;
		//This pawn will have no movement and will serve to interact with the UI
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

		//Getters
	class UCameraComponent* GetCameraComponent() { return camera_component; }
	class AGamePiece* GetGamePiece() { return current_gamepiece; }

		//Public Setters
	void SetGamePiece( AGamePiece* in_gamepiece);
	void SetPlayerName(FString in_name);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnLeftClick();

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* camera_component;

	UPROPERTY(Replicated)
	class AGamePiece* current_gamepiece;

	FString player_name;

 private:


};
