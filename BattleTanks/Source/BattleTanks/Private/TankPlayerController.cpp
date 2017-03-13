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
    // If it hits the landscape     
    if (FindSightRayHitLocation(HitLocation)) // does line tracing
    {
        // Tell controlled tank to aim at this point
        GetControlledTank()->AimAt(HitLocation);
    }
}

bool ATankPlayerController::FindSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

    FVector2D ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, 
                                         CrossHairYLocation * ViewportSizeY);

    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (!FindLookDirection(ScreenLocation, LookDirection)) { return false; };

    //Line-trace along that look direction, and see what we hit (up to max range)
    if (!FindLookVectorHitLocation(LookDirection, OUT HitLocation))
    {
        return false;
    }

    return true;    
}

bool ATankPlayerController::FindLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld ( ScreenLocation.X,
                                            ScreenLocation.Y,
                                            OUT CameraWorldLocation,
                                            OUT LookDirection
                                          );
}

bool ATankPlayerController::FindLookVectorHitLocation(const FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation   = StartLocation + LookDirection * LineTraceRange;

    bool res = GetWorld()->LineTraceSingleByChannel (HitResult,
                                                     StartLocation,
                                                     EndLocation,
                                                     ECollisionChannel::ECC_Visibility,
                                                     FCollisionQueryParams(),
                                                     FCollisionResponseParams()
                                                    );

    if (res)
    {
        HitLocation = HitResult.Location;
        return res;
    }

    HitLocation = FVector(0.0f);
    return res;

}
