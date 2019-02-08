// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    ATank* PlayerTank = GetPlayerTank();
    ATank* ControlledTank = GetControlledTank();
    
    if (!PlayerTank) {
        return;
    }
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    GetControlledTank()->Fire();
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
