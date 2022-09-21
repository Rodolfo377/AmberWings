// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	virtual void SetupInputComponent() override;

	//Control Callbacks
	void Pitch(float Value);
	void Yaw(float Value);
	void Roll(float Value);

	void Thrust(float Value);
};
