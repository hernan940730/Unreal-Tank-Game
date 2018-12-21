// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    ATank* ControlledTank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        return;
    }
    FVector HitLocation;
    bool HasHit = GetSightRayHitLocation(HitLocation);
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
    FVector2D CrosshairScreenPosition = GetCrosshairScreenPosition();
    FVector WorldLocation;
    FVector WorldDirection;
    if (DeprojectScreenPositionToWorld(CrosshairScreenPosition.X, CrosshairScreenPosition.Y, WorldLocation, WorldDirection)) {
        GetLookVectorHitLocation(OutHitLocation, WorldDirection);
        GetControlledTank()->AimAt(OutHitLocation);
        return true;
    }
    return false;
}

FVector2D ATankPlayerController::GetCrosshairScreenPosition() const {
    int32 ViewportXSize;
    int32 ViewportYSize;
    GetViewportSize(ViewportXSize, ViewportYSize);
    return FVector2D(ViewportXSize * CrosshairXLocation, ViewportYSize * CrosshairYLocation);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, const FVector& WorldDirection) const {
    FHitResult OutHitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (WorldDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(OutHitResult,
                                         StartLocation,
                                         EndLocation,
                                         ECC_Visibility,
                                         FCollisionQueryParams(FName(NAME_None), false, GetControlledTank()),
                                         FCollisionResponseParams(ECR_Block))) {
        OutHitLocation = OutHitResult.Location;
        return true;
    }
    return false;
}
