// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AWFlightController.h"

void AAWFlightController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Thrust", this, &AAWFlightController::Thrust);
	InputComponent->BindAxis("Pitch", this, &AAWFlightController::Pitch);
	InputComponent->BindAxis("Yaw", this, &AAWFlightController::Yaw);
	InputComponent->BindAxis("Roll", this, &AAWFlightController::Roll);
}

void AAWFlightController::Pitch(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Pitch: %f "), Value);
}

void AAWFlightController::Yaw(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Yaw: %f "), Value);
}

void AAWFlightController::Roll(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Roll: %f "), Value);
}

void AAWFlightController::Thrust(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Thrust: %f "), Value);
}

