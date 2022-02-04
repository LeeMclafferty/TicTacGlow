// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoard.generated.h"

UCLASS()
class TICTACTOE_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameBoard();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

		//Getters
	class UStaticMeshComponent* GetGameBoardMesh() { return gameboard_mesh; }

	UPROPERTY(EditAnywhere, Replicated)
	class UNiagaraSystem* explosion;

protected:
	virtual void BeginPlay() override;

		//Components
		// Will make 1 mesh in blender, I have added extra meshes in the bp to get the shapes
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* gameboard_mesh;



private:	

	//UPROPERTY()
	//TSubclassOf<AGameBoard> gameboard_class;

};
