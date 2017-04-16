// Copirtight Funny Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTankDeathDelegate);

/**
 * Tank is the base class of the Tank pawn controlled by the player through a Player Controller 
 * or by the AI through AI Controller.
 */
UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

    virtual float TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

    // Returns CurrentHealth as a percentage of StartingHealth between 0 and 1
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;

    FOnTankDeathDelegate OnDeath;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth; // Initialised in BeginPlay();
};
