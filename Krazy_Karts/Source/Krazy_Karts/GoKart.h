// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZY_KARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// The force applied when throttle held all the way down.
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	// Drag of the car.
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 100;

	
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = .010f;

	// The number of degrees per second at full steering throw.
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 90;

	// Mass of the car (kg).
	UPROPERTY(EditAnywhere)
	float Mass = 1000;


	FVector Velocity;
	FVector DriveForce;
	float Throttle;
	float SteeringThrow;
	
	void SetForward(float AxisValueIn);
	void MoveRight(float AxisValueIn);

	void ApplyRotation(float DeltaTime);
	void ApplyTranslation(float DeltaTime);

	FVector CalculateAirResistence();
	FVector CalculateRollResistance();
};
