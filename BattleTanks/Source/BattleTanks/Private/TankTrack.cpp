// Copirtight Funny Ltd.

#include "BattleTanks.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    // Calculate the slippage speed
    float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

    // Work-out the required acceleration this frame to correct
    FVector CorrectAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();
    
    // Calculate and apply sideways for (F = m a)
    UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    FVector CorrectionForce = (TankRoot->GetMass() * CorrectAcceleration) / 2; // Two tracks
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();

    UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


