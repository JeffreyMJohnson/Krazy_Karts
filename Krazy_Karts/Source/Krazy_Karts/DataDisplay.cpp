// Fill out your copyright notice in the Description page of Project Settings.

#include "DataDisplay.h"

#include "TextBlock.h"
#include "Engine/World.h"

#include "GoKart.h"




bool UDataDisplay::Initialize()
{
	if (!Super::Initialize()) return false;

	

	return true;

}

void UDataDisplay::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	if (!CarPawn)
	{
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PC = World->GetFirstPlayerController())
			{
				APawn* pawn = PC->GetPawn();
				CarPawn = Cast<AGoKart>(pawn);

				UE_LOG(LogTemp, Warning, TEXT("car pawn was %s bound."), CarPawn == nullptr ? TEXT("NOT") : TEXT(""));
			}

		}
	}

	if (SpeedText && CarPawn)
	{
		
		FText t = FText::FromString(FString::Printf(TEXT("Speed: %.2f m/sec"), CarPawn->GetVelocity().Size()));
		SpeedText->SetText(t);
	}

	if (TurnAngleText && CarPawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("speed: %f."), speed);
		FText t = FText::FromString(FString::Printf(TEXT("Turn Angle: %.3f degrees"), CarPawn->GetTurnAngle()));
		TurnAngleText->SetText(t);// CarPawn->GetVelocity().Size()
	}
//	UE_LOG(LogTemp, Warning, TEXT("Tick()."));
}
