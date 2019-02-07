// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"




// Sets default values ----- the constructor
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	//TankAimComponent pointing to its aim at function, not Tank aim at function
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed); //launch speed here only worked once TankAimingComponenet was setup
	
}

void ATank::Fire()
{
	 //protecting pointer. if there isnt one, no need to run the code 

	//Set timer and only fire if that timer has passed
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds; //can also use GetWorld and GetTimeSeconds instead. Platform time is not well documented

	//Spawn a projectile at the socketlocation
	if (Barrel && isReloaded) {
		auto ProjectileT = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		ProjectileT->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}