// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
    ATank* ControlledTank = GetControlledTank();
    if (ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing tank: %s"), *(ControlledTank->GetName()))
    }
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}
