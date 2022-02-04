// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamePiece.generated.h"

UCLASS()
class TICTACTOE_API AGamePiece : public AActor
{
	GENERATED_BODY()
	
public:	
	AGamePiece();
	virtual void Tick(float DeltaTime) override;

		//Getters
	class UStaticMeshComponent* GetGamePieceMesh() { return gamepiece_mesh; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* gamepiece_mesh;


public:	
	

};
