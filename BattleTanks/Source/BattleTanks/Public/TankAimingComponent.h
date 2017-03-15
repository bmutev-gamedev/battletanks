// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
    Locked,
    Aiming,
    Reloading
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:	
	UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

    void MoveBarrelTowards(FVector AimDirection);

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 10000; // TODO find sensible default

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.0f;

    double LastFireTime = 0;
};
