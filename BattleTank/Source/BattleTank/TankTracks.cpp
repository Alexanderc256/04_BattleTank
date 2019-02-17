// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive tracks
	//Apply sideways force
	ApplySidewaysForce();
}


void UTankTracks::ApplySidewaysForce()
{
	//Calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work out required acceleration this fram to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorretionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //- because we want opposite direction

																				//Calculate and apply sideways force (F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); //cast sceneroot to a ustaticmesh to get the physics properties from it
	auto CorrectionForce = TankRoot->GetMass() * CorretionAcceleration / 2; //divide by 2 because 2 tracks

	TankRoot->AddForce(CorrectionForce);
}

void UTankTracks::SetThrottle(float Throttle)
{
	//TODO Clamp throttle value, so player can't speed up, giving an unfair advantage
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTracks::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //Gone up hierarchy to owner, down to rootcomponent, and casted from a static mesh to a primitive component to add a force at location
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}