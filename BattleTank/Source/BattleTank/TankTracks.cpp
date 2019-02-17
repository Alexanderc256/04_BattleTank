// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work out required acceleration this fram to correct
	auto CorretionAcceleration = -SlippageSpeed / DeltaTime*GetRightVector(); //- because we want opposite direction

	//Calculate and apply sideways force (F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); //cast sceneroot to a ustaticmesh to get the physics properties from it
	auto CorrectionForce = TankRoot->GetMass() * CorretionAcceleration / 2; //divide by 2 because 2 tracks

	TankRoot->AddForce(CorrectionForce);

}

void UTankTracks::SetThrottle(float Throttle)
{
	//TODO Clamp throttle value, so player can't speed up, giving an unfair advantage

	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //Gone up hierarchy to owner, down to rootcomponent, and casted from a static mesh to a primitive component to add a force at location
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}