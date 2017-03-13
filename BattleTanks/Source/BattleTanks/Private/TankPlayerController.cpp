// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"

#define OUT

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
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return;}
    
    FVector HitLocation; // Out parameter
    if (FindSightRayHitLocation(HitLocation)) // does line tracing
    {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        // If it hits the landscape     // Tell controlled tank to aim at this point
    }
}

bool ATankPlayerController::FindSightRayHitLocation(FVector& HitLocation) const
{
    // Get current location
    // Calculate end line location
    // Do world line tracing based on static mesh
    // Return the HitLocation
    HitLocation = FVector(1.0f);
    return true;
}

