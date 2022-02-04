// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PieceSpawner.generated.h"

UENUM()
enum EOwner
{
	OWNER_None	UMETA(DisplayName = "None"),
	OWNER_X		UMETA(DisplayName = "X Owned"),
	OWNER_O		UMETA(DisplayName = "O Owned"),
};

UCLASS()
class TICTACTOE_API APieceSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APieceSpawner();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void SpawnGamePiece();

	UFUNCTION()
	void SetHasBeenTriggered(bool has_triggered) { has_been_triggered = has_triggered; }

	UPROPERTY(Replicated)
	bool has_been_triggered;

	EOwner eowner;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	class UBoxComponent* spawn_area;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SpawnGamePiece();


private:


};
