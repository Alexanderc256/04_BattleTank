// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
//Depends onn movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto TankAIController = Cast<ATank>(GetPawn());

	if (!ensure(PlayerTank)) { return; }
	if (ensure(PlayerTank)) {
		//Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); //30meters TODO check radius is in cm

		//aim towards player
		TankAIController->AimAt(PlayerTank->GetActorLocation());

		//shoot at player, if ready
		TankAIController->Fire(); //TODO Don't fire every frame
	}
	
}