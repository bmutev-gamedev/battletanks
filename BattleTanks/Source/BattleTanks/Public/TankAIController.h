// Copirtight Funny Ltd.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * TankAIController is the base class for the AI Controller Blueprint used to control
 * tanks or mortars.
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
    UFUNCTION()
    void OnTankDeath();
	
protected:
    virtual void BeginPlay() override;

    virtual void SetPawn(APawn* InPawn) override;

    // How Close can the AI tank get
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 8000;

private:
    virtual void Tick( float DeltaSeconds ) override;
};
