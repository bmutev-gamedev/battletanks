// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController did not possess a tank!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("PlayerController has possesed %s"), *ControlledTank->GetName());
}

void ATankPlayerController::Tick( float DeltaSeconds )
{
    Super::Tick(DeltaSeconds);
    // AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return;}

    // Get world location if linetrace through crosshair
    // If it hits the landscape
        // Tell controlled tank to aim at this point
}

