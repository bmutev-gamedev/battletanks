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
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
        // If it hits the landscape     // Tell controlled tank to aim at this point
    }
}

bool ATankPlayerController::FindSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

    FVector2D ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, 
                                         CrossHairYLocation * ViewportSizeY);

    
    FVector LookDirection;
    if (!GetLookDirection(ScreenLocation, LookDirection)) { return false; };

    // "De-project" the screen position of the crosshair to a world direction
    //Line-trace along that look direction, and see what we hit (up to max range)
    HitLocation = LookDirection;
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld ( ScreenLocation.X,
                                            ScreenLocation.Y,
                                            OUT CameraWorldLocation,
                                            OUT LookDirection
                                          );
}
