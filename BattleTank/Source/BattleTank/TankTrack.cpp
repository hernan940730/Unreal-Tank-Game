// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle) {
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::CorrectTrackSlippage() {
    const float DeltaTime = GetWorld()->GetDeltaSeconds();
    auto RightVector = GetRightVector();
    auto SlippageSpeed = FVector::DotProduct(RightVector, GetComponentVelocity());
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * RightVector;
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // There are two tracks
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
    DriveTrack();
    CorrectTrackSlippage();
    CurrentThrottle = 0;
}

void UTankTrack::DriveTrack() {
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
