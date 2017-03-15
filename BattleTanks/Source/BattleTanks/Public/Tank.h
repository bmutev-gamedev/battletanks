// Copirtight Funny Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetAimingComponentReference(UTankAimingComponent* AimingComponentToSet);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetBarrelReference(UTankBarrel* BarrelToSet);

    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;

private:	
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 100000; // TODO find sensible default

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

    // Local barrel reference for spawning projectile
    UTankBarrel* Barrel = nullptr;

    double LastFireTime = 0;
};
