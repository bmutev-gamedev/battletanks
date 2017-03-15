// Copirtight Funny Ltd.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
* TankTurret is used to rotate the turret of the tank with a given 
* relative speed.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // -1 is max downward speed, and +1 is max up movement
    void Rotate(float RelativeSpeed);
	
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 30;
};
