// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("AIPlayerController Begin Play"));

    ATank* PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIPlayerController did not detect a player tank!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("AIPlayerController has detected %s player tank!"), *PlayerTank->GetName());
}

void ATankAIController::Tick( float DeltaSeconds )
{
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    AActor* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerController found!"));
    }
    
    return Cast<ATank>(PlayerPawn);
}

// Move tank turret towards aim direction
void ATankAIController::AimTowardsCrosshair()
{
    if (GetPlayerTank())
    {
        // TODO Move towards the player

        // Tell controlled tank to aim at this point
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

        // Fire if ready
    }
}