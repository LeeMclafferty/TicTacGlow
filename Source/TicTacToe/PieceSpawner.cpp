

#include "PieceSpawner.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "TicTacToePawn.h"
#include "TicTacToePlayerController.h"
#include "GamePiece.h"

APieceSpawner::APieceSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	spawn_area = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));
	spawn_area->SetupAttachment(RootComponent);

	spawn_area->SetCollisionProfileName("Spawner");

	SetHasBeenTriggered(false);
	bReplicates = true;
	eowner = OWNER_None;
}

void APieceSpawner::BeginPlay()
{
	Super::BeginPlay();

	
}

void APieceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if(GetOwner() != NULL)
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("SpawnerOwer %s"), *GetOwner()->GetName()));*/


}

void APieceSpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APieceSpawner, has_been_triggered);
	//DOREPLIFETIME(APieceSpawner, eowner);

}

/// <summary>
/// I don't call any of this since clients cant call functions from actors they do not own. I moved the logic to the controller.
/// </summary>
void APieceSpawner::SpawnGamePiece()
{
	if(ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0 )))
	{	
			//If you are the server spawn the piece
		if(HasAuthority())
		{ 
			if(!has_been_triggered)
			{ 	AGamePiece* spawned_piece;
				FVector location = this->GetActorLocation();
				FRotator rotation(0.f, 0.f, 0.f);
				FVector scale(0.f, 0.f, 0.f);
				FActorSpawnParameters gamepiece_spawnparams;
				gamepiece_spawnparams.bNoFail = true;
		
				spawned_piece = GetWorld()->SpawnActor<AGamePiece>(player_controller->current_gamepiece_class, location, rotation, gamepiece_spawnparams);

				SetHasBeenTriggered(true);
			}
		}
			//If you are not call the Server RPC 
		if(!HasAuthority())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Client")));
			Server_SpawnGamePiece();
		}
	}
}

void APieceSpawner::Server_SpawnGamePiece_Implementation()
{
		//This Server RPC will just call spawn game piece again, but since the Server is doing it it will have authority and spawn it for the client
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Implementation")));
	SpawnGamePiece();
}

bool APieceSpawner::Server_SpawnGamePiece_Validate()
{
	return true;
}

