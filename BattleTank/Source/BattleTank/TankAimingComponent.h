// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
    Reloading,
    Aiming,
    Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    UFUNCTION(BlueprintCallable, Category = Setup)
    void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
    
    void AimAt(const FVector& WorldLocation);
    
    UFUNCTION(BlueprintCallable, Category = Firing)
    void Fire();

protected:
    
    UPROPERTY(BlueprintReadOnly, Category = State)
    EFiringState FiringState = EFiringState::Aiming;
    
private:
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> Projectile;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float TimeToReloadInSeconds = 3;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float FiringSpeed = 4000;
    
    UTankBarrel* Barrel;
    UTankTurret* Turret;
    
    double LastFiringTimeInSeconds = -3;
    
    void MoveBarrelTowards(const FVector& AimDirection);
    float GetMinDegreesMovement(const float& Degrees) const;
};
