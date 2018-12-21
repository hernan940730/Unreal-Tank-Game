// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    ATank* ControlledTank = GetControlledTank();
    ATank* PlayerTank = GetPlayerTank();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsPlayer();
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowardsPlayer() {
    ATank* PlayerTank = GetPlayerTank();
    if (PlayerTank) {
        GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
    }
}
