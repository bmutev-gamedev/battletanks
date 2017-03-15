// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Move tank turret towards aim direction
void ATankAIController::Tick( float DeltaSeconds )
{
    Super::Tick(DeltaSeconds);

    ATank* ControlledPawn = Cast<ATank>(GetPawn());
    ATank* PlayerPawn     = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (!ensure(PlayerPawn)) { return; }

    // TODO Move towards the player
    MoveToActor(PlayerPawn, AcceptanceRadius); // TODO check radius is in cm

    // Tell controlled tank to aim at this point
    ControlledPawn->AimAt(PlayerPawn->GetActorLocation());

    // Fire if ready
    ControlledPawn->Fire();
}