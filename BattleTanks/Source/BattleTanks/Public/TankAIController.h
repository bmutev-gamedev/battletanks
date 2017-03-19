// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

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
