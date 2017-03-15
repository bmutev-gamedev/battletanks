// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;

private:
    virtual void Tick( float DeltaSeconds ) override;

    // How Close can the AI tank get
    UPROPERTY(EditDefaultsOnly)
    float AcceptanceRadius = 3000;
};
