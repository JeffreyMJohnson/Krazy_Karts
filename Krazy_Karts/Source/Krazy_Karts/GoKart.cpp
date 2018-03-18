// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKart.h"

#include "Components/InputComponent.h"
#include "Engine/World.h"


// Sets default values
AGoKart::AGoKart()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DriveForce = Throttle * MaxDrivingForce * GetActorForwardVector();
	DriveForce += CalculateAirResistence();
	DriveForce += CalculateRollResistance();

	FVector Acceleration = DriveForce / Mass;

	Velocity += Acceleration * DeltaTime;

	ApplyRotation(DeltaTime);

	ApplyTranslation(DeltaTime);
}

FVector AGoKart::CalculateRollResistance()
{
	float AccelerationDueToGravity = Mass * -GetWorld()->GetGravityZ() / 100;
	return -Velocity.GetSafeNormal() * RollingResistanceCoefficient * AccelerationDueToGravity;
}

FVector AGoKart::CalculateAirResistence()
{
	float Speed = Velocity.Size();
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

void AGoKart::ApplyTranslation(float DeltaTime)
{
	// convert from cm/sec to m/sec 
	FVector Translation = 100 * Velocity * DeltaTime;
	FHitResult HitResult;
	AddActorWorldOffset(Translation, true, &HitResult);

	if (HitResult.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

void AGoKart::ApplyRotation(float DeltaTime)
{
	float DistanceDelta = FVector::DotProduct(GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = (DistanceDelta / MinTurningRadius) * SteeringThrow;
	FQuat RotationDelta(GetActorUpVector(), RotationAngle);
	Velocity = RotationDelta.RotateVector(Velocity);

	AddActorWorldRotation(RotationDelta);
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::SetForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);
}

void AGoKart::MoveRight(float AxisValueIn)
{
	SteeringThrow = AxisValueIn;
}

void AGoKart::SetForward(float AxisValueIn)
{
	Throttle = AxisValueIn;
}

