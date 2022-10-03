// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AWFlightController.h"
#include "Components/CapsuleComponent.h"

AAWFlightController::AAWFlightController():
PlanePawn(nullptr)
{

}

void AAWFlightController::BeginPlay()
{
	PlanePawn = Cast<AAWPlanePawn>(GetPawn());
	check(PlanePawn)
}

void AAWFlightController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Thrust", this, &AAWFlightController::Thrust);
	InputComponent->BindAxis("Pitch", this, &AAWFlightController::Pitch);
	InputComponent->BindAxis("Yaw", this, &AAWFlightController::Yaw);
	InputComponent->BindAxis("Roll", this, &AAWFlightController::Roll);
}

void AAWFlightController::Pitch(float Input)
{
	if (IsValid(PlanePawn) == false)
	{
		return;
	}
	float dt = GetWorld()->DeltaTimeSeconds;
	PlanePawn->AddActorWorldRotation(FRotator(PitchValue * Input * dt, 0, 0));
	UE_LOG(LogTemp, Warning, TEXT("Pitch: %f "), Input);
}

void AAWFlightController::Yaw(float Input)
{
	if (IsValid(PlanePawn) == false)
	{
		return;
	}
	float dt = GetWorld()->DeltaTimeSeconds;
	PlanePawn->AddActorWorldRotation(FRotator(0, YawValue * Input * dt, 0));
	UE_LOG(LogTemp, Warning, TEXT("Yaw: %f "), Input);
}

void AAWFlightController::Roll(float Input)
{
	if (IsValid(PlanePawn) == false)
	{
		return;
	}
	float dt = GetWorld()->DeltaTimeSeconds;
	PlanePawn->AddActorWorldRotation(FRotator(0, 0, RollValue * Input * dt));
	UE_LOG(LogTemp, Warning, TEXT("Roll: %f "), Input);
}

void AAWFlightController::Thrust(float Input)
{
	if (IsValid(PlanePawn) == false || IsValid(PlanePawn->CapsuleComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Plane Pawm or capsule invalid in  AAWFlightController::Thrust"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Thrust: %f "), Input);
	//PlanePawn->AirplaneMesh->AddForce(PlanePawn->GetActorForwardVector() * ThrustValue);
	PlanePawn->CapsuleComponent->AddForce(PlanePawn->GetActorForwardVector() * ThrustValue);
}

