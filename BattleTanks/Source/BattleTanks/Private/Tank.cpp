// Copirtight Funny Ltd.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void ATank::Fire()
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
