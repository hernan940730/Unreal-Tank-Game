// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);
    
protected:
    virtual void BeginPlay() override;
    
private:
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000000; //Asume 40 tons tank
    
    float CurrentThrottle = 0;
    
    UTankTrack();
    void CorrectTrackSlippage();
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    void DriveTrack();
};
