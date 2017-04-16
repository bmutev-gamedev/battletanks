// Copirtight Funny Ltd.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * TankBarrel is the base class for the barrel part of the tank turret and the mortar turret.
 *
 * This class holds the elevation constraints for the barrel.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // -1 is max downward speed, and +1 is max up movement
    void Elevate(float RelativeSpeed);
	
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 5;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxElevationDegrees = 20;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinElevationDegrees = 0;
	
};
