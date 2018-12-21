// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Tank.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(const FVector& WorldLocation, float FiringSpeed) {
    if (!Barrel || !Turret) {
        UE_LOG(LogTemp, Error, TEXT("No Barrel/Turret Component was found"))
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
    else {
        UE_LOG(LogTemp, Error, TEXT("%f: Solution was not found"), GetWorld()->GetTimeSeconds())
    }
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet) {
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurret(UTankTurret* TurretToSet) {
    Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection) {
    FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
    FRotator AimRotator = AimDirection.Rotation();
    FRotator DeltaRotator = AimRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Azimuth(GetMinDegreesMovement(DeltaRotator.Yaw));
}

float UTankAimingComponent::GetMinDegreesMovement(const float& Degrees) const {
    if ((Degrees >= 0 && Degrees <= 180) || (Degrees <= 0 && Degrees >= -180)) {
        return Degrees;
    }
    if (Degrees >= 0) {
        return Degrees - 360;
    }
    return Degrees + 360;
}
