// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Move tank turret towards aim direction
void ATankAIController::Tick( float DeltaSeconds )
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!ensure(PlayerPawn)) { return; }

    // TODO Move towards the player
    MoveToActor(PlayerPawn, AcceptanceRadius); // TODO check radius is in cm

    // Tell controlled tank to aim at this point
    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerPawn->GetActorLocation());

    // Fire if ready
    ATank* ControlledPawn = Cast<ATank>(GetPawn());
    ControlledPawn->Fire();
}