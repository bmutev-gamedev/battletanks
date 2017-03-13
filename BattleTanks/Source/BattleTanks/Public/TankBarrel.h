// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    void Elevate(float DegreesPerSecond);
	
private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 2;

    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegree = 20;

    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegree = 0;
	
};
