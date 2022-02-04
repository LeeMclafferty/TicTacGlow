// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class TICTACTOE_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloor();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, Replicated)
	class UStaticMeshComponent* floor_mesh;

	UFUNCTION(NetMulticast, Reliable)
	void DisableMesh();

protected:
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
