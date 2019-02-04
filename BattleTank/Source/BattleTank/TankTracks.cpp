// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle)
{
	//TODO Clamp throttle value, so player can't speed up, giving an unfair advantage

	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //Gone up hierarchy to owner, down to rootcomponent, and casted from a static mesh to a primitive component to add a force at location
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}