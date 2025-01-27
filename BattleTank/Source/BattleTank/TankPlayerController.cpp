// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) {
        return;
    }
    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
    if (!GetPawn()) {
        return;
    }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) {
        return;
    }
    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
        AimingComponent->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
    FVector2D CrosshairScreenPosition = GetCrosshairScreenPosition();
    FVector WorldLocation;
    FVector WorldDirection;
    return DeprojectScreenPositionToWorld(CrosshairScreenPosition.X, CrosshairScreenPosition.Y, WorldLocation, WorldDirection)
            && GetLookVectorHitLocation(OutHitLocation, WorldDirection);
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
                                         FCollisionQueryParams(FName(NAME_None), false, GetPawn()),
                                         FCollisionResponseParams(ECR_Block))) {
        OutHitLocation = OutHitResult.Location;
        return true;
    }
    return false;
}
