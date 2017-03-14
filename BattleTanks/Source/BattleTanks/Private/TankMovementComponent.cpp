// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    if (!LeftTrackToSet)  { return; }
    if (!RightTrackToSet) { return; }

    LeftTrack  = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
    UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw)

    // TODO Prevent double-speed due to dual control use
}

