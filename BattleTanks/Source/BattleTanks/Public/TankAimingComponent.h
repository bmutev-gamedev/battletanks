// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
    Locked,
    Aiming,
    Reloading
};

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:	
	UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    void MoveBarrelTowards(FVector AimDirection);

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 100000; // TODO find sensible default
};
