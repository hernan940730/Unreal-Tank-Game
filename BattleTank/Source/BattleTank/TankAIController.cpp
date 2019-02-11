// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    auto PlayerTank = GetPlayerTank();
    
    if (!ensure(PlayerTank)) {
        return;
    }
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    if (!ensure(AimingComponent)) {
        return;
    }
    
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    if (AimingComponent->GetFiringState() == EFiringState::Locked) {
        AimingComponent->Fire();
    }
}

APawn* ATankAIController::GetPlayerTank() const {
    return GetWorld()->GetFirstPlayerController()->GetPawn();
}
