// Copirtight Funny Ltd.

#include "BattleTanks.h"
#include "AutoMortars.h"


// Sets default values
AAutoMortars::AAutoMortars()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

}

void AAutoMortars::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = StartingHealth;
}

float AAutoMortars::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);

    float DamageToApply = FMath::Clamp<float>(DamagePoints, 0, CurrentHealth);
    UE_LOG(LogTemp, Warning, TEXT("Tank is hit for %f damage and receives %f damage"), DamageAmount, DamageToApply)

        CurrentHealth -= (int32)DamageToApply;

    if (CurrentHealth <= 0)
    {
        OnDeath.Broadcast();
    }

    return DamageToApply;
}

float AAutoMortars::GetHealthPercent() const
{
    return (float)CurrentHealth / (float)StartingHealth;
}
