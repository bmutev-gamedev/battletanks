// Copirtight Funny Ltd.

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

    // First fire should start after initial reload
    LastFireTime = FPlatformTime::Seconds();
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

    if (BulletsAmmo <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }

}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

int32 UTankAimingComponent::GetBulletsCount() const
{
    return BulletsAmmo;
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    return !AimDirection.Equals(Barrel->GetForwardVector(), 0.1f);
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
        AimDirection = LaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirectionToUse)
{
    if (!ensure(Barrel)) { return; }
    if (!ensure(Turret)) { return; }

    // Work-out difference between current barrel rotation and AimDirectionToUse
    FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
    FRotator AimAsRotator = AimDirectionToUse.Rotation();
    FRotator DeltaRotator = AimAsRotator - BarrelRotator;
    //UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

    Barrel->Elevate(DeltaRotator.Pitch);

    if (FMath::Abs(DeltaRotator.Yaw) < 180)
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
    else
    {
        Turret->Rotate(-DeltaRotator.Yaw);
    }    
}

void UTankAimingComponent::Fire()
{
    if (FiringState == EFiringState::Locked ||
        FiringState == EFiringState::Aiming)
    {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }

        // Spawn projectile at barrel location
        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint, 
            Barrel->GetSocketLocation(FName("Projectile")), 
            Barrel->GetSocketRotation(FName("Projectile"))
            );

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        BulletsAmmo--;
    }

}