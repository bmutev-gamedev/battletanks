// Copirtight Funny Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

    virtual float TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, Category = "Health")
        int32 CurrentHealth = StartingHealth;
};
