// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	
    UTankAimingComponent* TankAimingComponent = nullptr;
    
	virtual void BeginPlay() override;
    
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    void AimAt(const FVector& Location);
    
    UFUNCTION(BlueprintCallable, Category = Firing)
    void Fire();
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* TurretToSet);
    
private:
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float FiringSpeed = 100000;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float TimeToReloadInSeconds = 3;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> Projectile;
    
    UTankBarrel* Barrel = nullptr;
    
    double LastFiringTimeInSeconds = -3;
    
};
