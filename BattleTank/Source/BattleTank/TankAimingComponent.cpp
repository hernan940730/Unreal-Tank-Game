// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "GenericPlatform/GenericPlatformMath.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    AimDirection = FVector(0, 0, 0);
}

void UTankAimingComponent::BeginPlay() {
    LastFiringTimeInSeconds = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SetFiringState();
}

void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) {
    Turret = TurretToSet;
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(const FVector& WorldLocation) {
    if (!ensure(Barrel && Turret)) {
        return;
    }
    
    FVector OutFiringVelocity;
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
                                                                        OutFiringVelocity,
                                                                        Barrel->GetSocketLocation(FName("Projectile")),
                                                                        WorldLocation,
                                                                        FiringSpeed,
                                                                        false,
                                                                        0,
                                                                        0,
                                                                        ESuggestProjVelocityTraceOption::DoNotTrace);
    if (bHaveAimSolution) {
        FVector AimDirection = OutFiringVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::Fire() {
    UClass* ProjectileClass = Projectile.Get();
    if (!ensure(Barrel && ProjectileClass)) {
        return;
    }
    if (FiringState == EFiringState::Reloading) {
        return;
    }
    
    LastFiringTimeInSeconds = FPlatformTime::Seconds();
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
                                                                  Barrel->GetSocketLocation(FName("Projectile")),
                                                                  Barrel->GetSocketRotation(FName("Projectile")),
                                                                  FActorSpawnParameters());
    
    Projectile->LaunchProjectile(FiringSpeed);
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection) {
    this->AimDirection = AimDirection;
    if (!ensure(Barrel && Turret)) {
        return;
    }
    
    FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
    FRotator AimRotator = AimDirection.Rotation();
    FRotator DeltaRotator = AimRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Azimuth(GetMinDegreesMovement(DeltaRotator.Yaw));
}

float UTankAimingComponent::GetMinDegreesMovement(const float& Degrees) const {
    if (FMath::Abs(Degrees) <= 180) {
        return Degrees;
    }
    if (Degrees >= 0) {
        return Degrees - 360;
    }
    return Degrees + 360;
}

void UTankAimingComponent::SetFiringState() {
    if (IsReloading()) {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving()) {
        FiringState = EFiringState::Aiming;
    }
    else {
        FiringState = EFiringState::Locked;
    }
}

bool UTankAimingComponent::IsReloading() {
    return FPlatformTime::Seconds() - LastFiringTimeInSeconds < TimeToReloadInSeconds;
}

bool UTankAimingComponent::IsBarrelMoving() {
    if (!ensure(Barrel)) {
        return true;
    }
    return !Barrel->GetForwardVector().Equals(AimDirection, 0.1);
}


EFiringState UTankAimingComponent::GetFiringState() {
    return FiringState;
}
