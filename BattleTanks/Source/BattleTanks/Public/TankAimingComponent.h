// Copirtight Funny Ltd.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Locked,
    Aiming,
    Reloading,
    OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

/**
 * TankAimingComponent when attached to a tank or mortar pawn is used to move the turret and barrel parts,
 * to "fire" a projectile from the barrel and to track the firing state.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

    void AimAt(FVector HitLocation);

    EFiringState GetFiringState() const;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    int32 GetBulletsCount() const;

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;

private:	
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void MoveBarrelTowards(FVector AimDirectionToUse);

    bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 8000; // TODO find sensible default

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 BulletsAmmo = 3;

    double LastFireTime = 0;

    FVector AimDirection = FVector(0, 0, 0);
};
