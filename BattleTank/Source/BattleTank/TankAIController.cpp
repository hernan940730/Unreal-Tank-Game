// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    ATank* ControlledTank = GetControlledTank();
    ATank* PlayerTank = GetPlayerTank();
    if (ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing tank: %s"), *(ControlledTank->GetName()))
    }
    if (PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("AIController targeting to tank: %s"), *(PlayerTank->GetName()))
    }
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
