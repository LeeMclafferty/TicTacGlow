
#include "TicTacToePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "TicTacToePlayerController.h"
#include "GamePiece.h"
#include "TicTacToeGameInstance.h"

ATicTacToePawn::ATicTacToePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera_component->SetupAttachment(RootComponent);

}

void ATicTacToePawn::BeginPlay()
{
	Super::BeginPlay();

	//if(HasAuthority())
	//{ 
	//	SetGamePieceClass(true);
	//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Is X: %i"), is_x_piece));
	//}
	//if(!HasAuthority())
	//{ 
	//	SetGamePieceClass(false);
	//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Is X: %i"), is_x_piece));

	//}

}

void ATicTacToePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

// 	if(ATicTacToePlayerController* pc = Cast<ATicTacToePlayerController>(GetController()))
// 		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Purple, FString::Printf(TEXT("class: %ul"), pc->current_gamepiece_class));

}

void ATicTacToePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TrySpawnPiece", IE_Pressed, this, &ATicTacToePawn::OnLeftClick);

}

void ATicTacToePawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATicTacToePawn, current_gamepiece);

}


void ATicTacToePawn::SetGamePiece(AGamePiece* in_gamepiece)
{
	current_gamepiece = in_gamepiece;
}

void ATicTacToePawn::SetPlayerName(FString in_name)
{
	player_name = in_name;
}

void ATicTacToePawn::OnLeftClick()
{
	if (ATicTacToePlayerController* player_controller = Cast<ATicTacToePlayerController>(GetController()))
	{
		player_controller->TraceUnderCursor();
		//UE_LOG(LogTemp, Log, TEXT("click"))
	}
}