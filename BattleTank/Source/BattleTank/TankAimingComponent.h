// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for firiing status
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

//forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

//Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeComponent(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	int32 GetRoundsLeft() const;

	

protected:
	//Enum initialization
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;


private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float LaunchSpeed = 4000; //4000m/s

	double LastFireTime = 0;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;

};
