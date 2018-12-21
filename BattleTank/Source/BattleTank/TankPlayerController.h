// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    void BeginPlay() override;
    
private:
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5;
    
    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.3;
    
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000;
    
    ATank* GetControlledTank() const;
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    FVector2D GetCrosshairScreenPosition() const;
    bool GetLookVectorHitLocation(FVector& OutHitLocation, const FVector& WorldDirection) const;
public:
    void Tick(float DeltaTime) override;
};
