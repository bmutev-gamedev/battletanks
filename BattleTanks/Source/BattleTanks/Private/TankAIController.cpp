// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h" // So we can implement OnDeath()
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

    // if aim or locked
    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();
    }
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        ATank* PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }
}

void ATankAIController::OnTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("DEATH!"))
}