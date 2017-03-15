// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel)) { return; }

    FVector LaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
        (
            this,
        OUT LaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0,
            0,
            ESuggestProjVelocityTraceOption::DoNotTrace
        );

    if (bHaveAimSolution)
    {
        FVector AimDirection = LaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if (!ensure(Barrel)) { return; }
    if (!ensure(Turret)) { return; }

    // Work-out difference between current barrel rotation and AimDirection
    FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
    FRotator AimAsRotator = AimDirection.Rotation();
    FRotator DeltaRotator = AimAsRotator - BarrelRotator;
    //UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
    if (!ensure(Barrel)) { return; }
    if (!ensure(ProjectileBlueprint)) { return; }

    bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    if (bIsReloaded)
    {
        // Spawn projectile at barrel location
        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint, 
            Barrel->GetSocketLocation(FName("Projectile")), 
            Barrel->GetSocketRotation(FName("Projectile"))
            );

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }

}