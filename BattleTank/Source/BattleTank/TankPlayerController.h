// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    void BeginPlay() override;
    
    UFUNCTION(BlueprintImplementableEvent, Category = Setup)
    void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);
    
private:
    UPROPERTY(EditDefaultsOnly)
    float CrosshairXLocation = 0.5;
    
    UPROPERTY(EditDefaultsOnly)
    float CrosshairYLocation = 0.3;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000;
    
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    FVector2D GetCrosshairScreenPosition() const;
    bool GetLookVectorHitLocation(FVector& OutHitLocation, const FVector& WorldDirection) const;
    
public:
    void Tick(float DeltaTime) override;
};
