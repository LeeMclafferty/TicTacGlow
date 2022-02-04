// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameReferee.generated.h"

UCLASS()
class TICTACTOE_API AGameReferee : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameReferee();

	void CheckWin();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner01;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner02;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner03;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner04;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner05;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner06;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner07;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner08;
	UPROPERTY(EditAnywhere, Category = "Spawners")
	class APieceSpawner* spawner09;

public:	
	virtual void Tick(float DeltaTime) override;

};
