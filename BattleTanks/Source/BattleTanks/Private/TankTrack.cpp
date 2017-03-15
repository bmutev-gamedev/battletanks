// Copirtight Funny Ltd.

#include "BattleTanks.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
    // TODO Fix ensure error when doing AddDynamic
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    DriveTrack();
    ApplySideWaysForce();
    CurrentThrottle = 0.0f;
}

void UTankTrack::ApplySideWaysForce()
{
    // Calculate the slippage speed
    float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

    // Work-out the required acceleration this frame to correct
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    FVector CorrectAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();

    // Calculate and apply sideways for (F = m a)
    UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    FVector CorrectionForce = (TankRoot->GetMass() * CorrectAcceleration) / 2; // Two tracks
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
    FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();

    UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
