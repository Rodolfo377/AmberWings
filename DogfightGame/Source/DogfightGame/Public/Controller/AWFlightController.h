// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Pawns/AWPlanePawn.h"
#include "Templates/UniquePtr.h"
#include "AWFlightController.generated.h"

/**
 * AW Flight Controller

Flight Commands: 3 Directional Control

Yaw
Pitch
Roll
 */
UCLASS()
class DOGFIGHTGAME_API AAWFlightController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAWFlightController();

	void BeginPlay() override;

	virtual void SetupInputComponent() override;

	//Control Callbacks
	void Pitch(float Value);
	void Yaw(float Value);
	void Roll(float Value);

	void Thrust(float Value);

protected:
	AAWPlanePawn* PlanePawn;

public:
	UPROPERTY(EditAnywhere, Category = "AmberWings|FlightController")
	float PitchValue;
	UPROPERTY(EditAnywhere, Category = "AmberWings|FlightController")
	float RollValue;
	UPROPERTY(EditAnywhere, Category = "AmberWings|FlightController")
	float YawValue;

	UPROPERTY(EditAnywhere, Category = "AmberWings|FlightController")
	float ThrustValue;
};
