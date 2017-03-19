// Copirtight Funny Ltd.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
* Responsible for helping the player control the tank
*/
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    UFUNCTION()
    void OnTankDeath();
	
protected:
    virtual void BeginPlay() override;

    virtual void SetPawn(APawn* InPawn) override;

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
    virtual void Tick( float DeltaSeconds ) override;

    // Move tank turret towards aim direction
    void AimTowardsCrosshair();

    // Find the potential hit location based on aim
    bool FindSightRayHitLocation(FVector& HitLocation) const;

    // "De-project" the screen position of the crosshair to a world direction
    bool FindLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

    // Line-trace along given look direction, and see what was hit (up to max range)
    bool FindLookVectorHitLocation(const FVector LookDirection, FVector& HitLocation) const;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.333f;

    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 200000.0f; // 2km
};
