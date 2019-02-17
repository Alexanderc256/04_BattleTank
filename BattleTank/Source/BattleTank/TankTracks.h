// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * TankTracks is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent)) //adds custom component
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);



	//This is max force per track, in Newtons (F=ma)
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 40000000; //40000kg tank * (10ms-2 = 1g) acceleration

private:
	UTankTracks();

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

	void DriveTrack();

	float CurrentThrottle = 0;
};
