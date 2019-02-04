// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto TankAIController = Cast<ATank>(GetPawn());

	if (!PlayerTank) { return; }
	if (PlayerTank) {
		//TODO move towards player

		//aim towards player
		TankAIController->AimAt(PlayerTank->GetActorLocation());

		//shoot at player, if ready
		TankAIController->Fire(); //TODO Don't fire every frame
	}
	
}