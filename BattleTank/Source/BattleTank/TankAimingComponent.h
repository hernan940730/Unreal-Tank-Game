// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void AimAt(const FVector& WorldLocation, float FiringSpeed);
    void SetBarrel(UTankBarrel* BarrelToSet);
    void SetTurret(UTankTurret* TurretToSet);
    
private:
    UTankBarrel* Barrel;
    UTankTurret* Turret;
    
    void MoveBarrelTowards(const FVector& AimDirection);
    float GetMinDegreesMovement(const float& Degrees) const;
};