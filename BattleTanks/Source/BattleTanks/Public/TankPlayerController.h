// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;

private:
    virtual void Tick( float DeltaSeconds ) override;

    ATank* GetControlledTank() const;

    // Move tank turret towards aim direction
    void AimTowardsCrosshair();

    // Find the potential hit location based on aim
    bool FindSightRayHitLocation(FVector& HitLocation) const;

    // "De-project" the screen position of the crosshair to a world direction
    bool FindLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

    // Line-trace along given look direction, and see what was hit (up to max range)
    bool FindLookVectorHitLocation(const FVector LookDirection, FVector& HitLocation) const;

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.333f;

    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.0f; // 10km
};
