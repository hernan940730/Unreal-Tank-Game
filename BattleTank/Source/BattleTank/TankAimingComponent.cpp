// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(const FVector& WorldLocation, float FiringSpeed) {
    if (!Barrel) {
        return;
    }
    
    FVector OutFiringVelocity;
    bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
                                                                   OutFiringVelocity,
                                                                   Barrel->GetSocketLocation(FName("Projectile")),
                                                                   WorldLocation,
                                                                   FiringSpeed,
                                                                   ESuggestProjVelocityTraceOption::DoNotTrace);
    if (bHaveAimSolution) {
        FVector AimDirection = OutFiringVelocity.GetSafeNormal();
        MoveBarrelTowards();
    }
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* BarrelToSet) {
    Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection) {
    FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
    FRotator AimRotator = AimDirection.Rotation();
    FRotator DeltaRotator = AimRotator - BarrelRotator;
    
}
