// Copirtight Funny Ltd.

#include "BattleTanks.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the barrel the right amount this fram
    // Given a max elevation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}

