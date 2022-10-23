// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"

#include "Math/UnrealMathUtility.h"

UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	OriginalRotation = GetOwner()->GetActorRotation();

}


void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = OriginalLocation;
	FRotator TargetRotation = OriginalRotation;
	if (ShouldMove == true)
	{
		TargetLocation = OriginalLocation + MoveOffset;
		TargetRotation = OriginalRotation + RotateOffset;
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	
	float MoveSpeed = MoveOffset.Length() / MoveTime;
	float RotationSpeed = 90 / RotateTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
	GetOwner()->SetActorLocation(NewLocation);

	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);
	GetOwner()->SetActorRotation(NewRotation);
	
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}
