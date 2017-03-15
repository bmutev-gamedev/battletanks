// Copirtight Funny Ltd.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent))
    {
        FoundAimingComponent(AimingComponent);
    }  
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"))
    }
}

void ATankPlayerController::Tick( float DeltaSeconds )
{
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}

// Move tank turret towards aim direction
void ATankPlayerController::AimTowardsCrosshair()
{
    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    
    FVector HitLocation; // Out parameter
    // If it hits the landscape     
    if (FindSightRayHitLocation(HitLocation)) // does line tracing
    {
        // Tell controlled tank to aim at this point
        AimingComponent->AimAt(HitLocation);
    }
}

// Find the potential hit location based on aim
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

// "De-project" the screen position of the crosshair to a world direction
bool ATankPlayerController::FindLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld ( ScreenLocation.X,
                                            ScreenLocation.Y,
                                            OUT CameraWorldLocation,
                                            OUT LookDirection
                                          );
}

// Line-trace along given look direction, and see what was hit (up to max range)
bool ATankPlayerController::FindLookVectorHitLocation(const FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation   = StartLocation + LookDirection * LineTraceRange;

    bool res = GetWorld()->LineTraceSingleByChannel (HitResult,
                                                     StartLocation,
                                                     EndLocation,
                                                     ECollisionChannel::ECC_Visibility
                                                    );

    // TODO Check why res is always TRUE
    if (res)
    {
        HitLocation = HitResult.Location;
        return res;
    }

    HitLocation = FVector(0.0f);
    return res;

}
