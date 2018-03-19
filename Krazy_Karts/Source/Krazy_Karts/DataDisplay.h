// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DataDisplay.generated.h"

/**
 * 
 */
UCLASS()
class KRAZY_KARTS_API UDataDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SpeedText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TurnAngleText;

	UPROPERTY()
	class AGoKart* CarPawn;	
	
	
};
