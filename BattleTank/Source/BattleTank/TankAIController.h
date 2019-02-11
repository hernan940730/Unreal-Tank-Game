// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
    
protected:
    void BeginPlay() override;
    
private:
    APawn* GetPlayerTank() const;
    
    UPROPERTY(EditAnywhere, Category = Setup)
    float AcceptanceRadius = 8000;
    
public:
    void Tick(float DeltaTime) override;
};
