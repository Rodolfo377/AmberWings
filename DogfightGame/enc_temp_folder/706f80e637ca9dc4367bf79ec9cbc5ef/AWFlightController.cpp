// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AWFlightController.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

AAWFlightController::AAWFlightController():
PlanePawn(nullptr)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAWFlightController::BeginPlay()
{
	PlanePawn = Cast<AAWPlanePawn>(GetPawn());
	check(PlanePawn)
}

void AAWFlightController::Tick(float DeltaTime)
{
	if (IsValid(PlanePawn) == false || IsValid(PlanePawn->CapsuleComponent) == false)
	{
		return;
	}

	FVector Movement = PlanePawn->GetVelocity();

	CurrentSpeed = FVector::DotProduct(Movement, PlanePawn->GetActorForwardVector());
	UE_LOG(LogTemp, Warning, TEXT("Movement Speed: %f"), CurrentSpeed);
	//FVector SidewaysMovement = Movement * FVector::DotProduct(Movement, PlanePawn->GetActorRightVector());

	

	//TODO Debug Sideways Movement with debug draw. Too much force being applied, find out where from.

	FVector LinearDragForce = Movement * LinearDragValue * PlanePawn->CapsuleComponent->GetMass();
	
	FVector ResultForce = Acceleration;

	

	if (CurrentSpeed > 0)
	{
		ResultForce -= LinearDragForce;
	}

	UE_LOG(LogTemp, Warning, TEXT("ResultForce: %f , %f, %f"), ResultForce.X, ResultForce.Y, ResultForce.Z);
	FVector SidewaysMovement = PlanePawn->GetActorRightVector() * FVector::DotProduct(Movement, PlanePawn->GetActorRightVector());

	ResultForce -= SidewaysMovement * SidewaysDragValue;

	FVector VerticalMovement = PlanePawn->GetActorUpVector() * FVector::DotProduct(Movement, PlanePawn->GetActorUpVector());

	PlanePawn->CapsuleComponent->AddForce(ResultForce);
	ResultForce -= VerticalMovement * VerticalDragValue;

	if (DebugDraw)
	{
		//DrawDebugLine(GetWorld(), PlanePawn->GetActorLocation(), PlanePawn->GetActorLocation() + SidewaysMovement * 100, FColor::Blue, false, 0.5f, 0, 3.f);
		DrawDebugLine(GetWorld(), PlanePawn->GetActorLocation(), PlanePawn->GetActorLocation() - VerticalMovement.GetSafeNormal() * 100, FColor::Green, false, 0.5f, 0, 3.f);
		DrawDebugLine(GetWorld(), PlanePawn->GetActorLocation(), PlanePawn->GetActorLocation() - SidewaysMovement.GetSafeNormal() * 100, FColor::Red, false, 0.5f, 0, 3.f);
		DrawDebugLine(GetWorld(), PlanePawn->GetActorLocation(), PlanePawn->GetActorLocation() - ResultForce.GetSafeNormal() * 200, FColor::Blue, false, 0.1f, 0, 3.f);
	}
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
	PlanePawn->AddActorLocalRotation(FRotator(PitchValue * Input * dt, 0, 0));
	UE_LOG(LogTemp, Warning, TEXT("Pitch: %f "), Input);
}

void AAWFlightController::Yaw(float Input)
{
	if (IsValid(PlanePawn) == false)
	{
		return;
	}
	float dt = GetWorld()->DeltaTimeSeconds;
	PlanePawn->AddActorLocalRotation(FRotator(0, YawValue * Input * dt, 0));
	UE_LOG(LogTemp, Warning, TEXT("Yaw: %f "), Input);
}

void AAWFlightController::Roll(float Input)
{
	if (IsValid(PlanePawn) == false)
	{
		return;
	}
	float dt = GetWorld()->DeltaTimeSeconds;
	PlanePawn->AddActorLocalRotation(FRotator(0, 0, RollValue * Input * dt));
	UE_LOG(LogTemp, Warning, TEXT("Roll: %f "), Input);
}

void AAWFlightController::Thrust(float Input)
{
	if (IsValid(PlanePawn) == false || IsValid(PlanePawn->CapsuleComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Plane Pawm or capsule invalid in  AAWFlightController::Thrust"));
		return;
	}

	Acceleration = FVector(0);
	if (Input > 0 && CurrentSpeed < TopSpeed)
	{	
		UE_LOG(LogTemp, Warning, TEXT("Thrust: %f "), Input);
		//PlanePawn->AirplaneMesh->AddForce(PlanePawn->GetActorForwardVector() * ThrustValue);
		//PlanePawn->CapsuleComponent->AddForce(PlanePawn->GetActorForwardVector() * ThrustValue);
		Acceleration = PlanePawn->GetActorForwardVector()* ThrustValue;
	}
}

