// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Azimuth(float RelativeSpeed) {
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    float AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float YawNewAzimuth = RelativeRotation.Yaw + AzimuthChange;
    SetRelativeRotation(FRotator(0, YawNewAzimuth, 0));
}
