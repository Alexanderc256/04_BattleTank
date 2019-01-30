// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
		ATank* GetTankAIController() const; //const because not going to change anything

		ATank* GetPlayerTank() const;

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
};