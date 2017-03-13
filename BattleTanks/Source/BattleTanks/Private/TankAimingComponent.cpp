// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
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

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel) { return; }

    FVector LaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    // Calculate the LaunchVelocity
    if (UGameplayStatics::SuggestProjectileVelocity(
            this,
        OUT LaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0,
            0,
            ESuggestProjVelocityTraceOption::DoNotTrace
        ))
    {
        FVector AimDirection = LaunchVelocity.GetSafeNormal();
        FString TankName = GetOwner()->GetName();
        UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
    }
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
    Barrel = BarrelToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

