// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = (Tank))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
    
public:
    void Azimuth(float RelativeSpeed);
    
private:
    UPROPERTY(EditDefaultsOnly)
    float MaxDegreesPerSecond = 20;
};
