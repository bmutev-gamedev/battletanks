// Copirtight Funny Ltd.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

/**
 * Projectile is a base class for the projectile actor, spawned when a gun is fired.
 */
UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

    void LaunchProjectile(float Speed);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* LaunchBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* ImpactBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    URadialForceComponent* ExplosionForce = nullptr;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    void OnTimerExpire();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestroyDelay = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ProjectileDamage = 20.0f;
};
