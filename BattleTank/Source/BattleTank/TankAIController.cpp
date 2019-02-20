// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
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

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) && ControlledTank) { return; }

	if (ensure(PlayerTank)) {
		//Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); //30meters TODO check radius is in cm

		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		//aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}
	}

	
}