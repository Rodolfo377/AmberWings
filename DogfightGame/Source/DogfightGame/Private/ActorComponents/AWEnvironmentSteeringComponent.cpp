// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AWEnvironmentSteeringComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Controller/AWFlightController.h"


// Sets default values for this component's properties
UAWEnvironmentSteeringComponent::UAWEnvironmentSteeringComponent():
 OwnerController(nullptr),
 OwnerActor(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UAWEnvironmentSteeringComponent::BeginPlay()
{
	Super::BeginPlay();
	auto Owner = GetOwner();
	/*OwnerController = Cast<AAWFlightController>(GetOwner());
	check(OwnerController);*/

	OwnerActor = Cast<AAWPlanePawn>(GetOwner());
	check(OwnerActor);
	
	//XYEnvinromentPlane = NewOb
}

void UAWEnvironmentSteeringComponent::BuildEnvironmentPlane(FAWEnvironmentPlane& Plane)
{
	//XY plane (horizontal to fighter jet)
	if (Plane.Mode == 1)
	{
		float deltaAngleDegrees = 360.0f / Plane.TotalRadials;		
		float deltaAngleRadians = deltaAngleDegrees * PI/180.0f;
		for (int i = 0; i < Plane.TotalRadials; i++)
		{
			FQuat q = FQuat(OwnerActor->GetActorUpVector(), deltaAngleRadians * i);
			FVector QuaternionRotatedVector = q.RotateVector(OwnerActor->GetActorForwardVector());
			Plane.InterestPlane.Add(i, QuaternionRotatedVector);
		}
		
		for (TPair<int32, FVector>& RadialDirection : Plane.InterestPlane)
		{
			if (bDebugDrawEnabled)
			{
				DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + RadialDirection.Value * 200.0f, FColor::Green, false, -1, 0, 5);
			}

			if (bDebugLogEnabled)
			{
				UE_LOG(LogTemp, Warning, TEXT(" Radial %d: (%f, %f, %f) "), RadialDirection.Key,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).X,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).Y,
					OwnerActor->GetActorLocation().Z);
			}
		} 
	}

	//YZ plane - goes along the fighter jet
	if (Plane.Mode == 2)
	{
		float deltaAngleDegrees = 360.0f / Plane.TotalRadials;
		float deltaAngleRadians = deltaAngleDegrees * PI / 180.0f;
		for (int i = 0; i < Plane.TotalRadials; i++)
		{
			FQuat q = FQuat(OwnerActor->GetActorRightVector(), deltaAngleRadians * i);
			FVector QuaternionRotatedVector = q.RotateVector(OwnerActor->GetActorForwardVector());
			Plane.InterestPlane.Add(i, QuaternionRotatedVector);
		}

		for (TPair<int32, FVector>& RadialDirection : Plane.InterestPlane)
		{
			if (bDebugDrawEnabled)
			{
				DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + RadialDirection.Value * 200.0f, FColor::Blue, false, -1, 0, 5);
			}

			if (bDebugLogEnabled)
			{
				UE_LOG(LogTemp, Warning, TEXT(" Radial %d: (%f, %f, %f) "), RadialDirection.Key,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).X,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).Y,
					OwnerActor->GetActorLocation().Z);
			}
		}
	}

	//XZ plane - goes across the fighter jet
	if (Plane.Mode == 3)
	{
		float deltaAngleDegrees = 360.0f / Plane.TotalRadials;
		float deltaAngleRadians = deltaAngleDegrees * PI / 180.0f;
		for (int i = 0; i < Plane.TotalRadials; i++)
		{
			FQuat q = FQuat(OwnerActor->GetActorForwardVector(), deltaAngleRadians * i);
			FVector QuaternionRotatedVector = q.RotateVector(OwnerActor->GetActorUpVector());
			Plane.InterestPlane.Add(i, QuaternionRotatedVector);
		}

		for (TPair<int32, FVector>& RadialDirection : Plane.InterestPlane)
		{
			if (bDebugDrawEnabled)
			{
				DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + RadialDirection.Value * 200.0f, FColor::Red, false, -1, 0, 5);
			}

			if (bDebugLogEnabled)
			{
				UE_LOG(LogTemp, Warning, TEXT(" Radial %d: (%f, %f, %f) "), RadialDirection.Key,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).X,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).Y,
					OwnerActor->GetActorLocation().Z);
			}
		}
	}
}


void UAWEnvironmentSteeringComponent::ProcessEnvironmentPlaneMap(FAWEnvironmentPlane& EnvironmentPlane, const FGameplayTagContainer& Tags)
{
}

void UAWEnvironmentSteeringComponent::GenerateEnvironmentPlaneMapResult(FAWEnvironmentPlane& EnvironmentPlane)
{
}

FVector UAWEnvironmentSteeringComponent::CalculateEnviromentSteeringVector()
{
	return FVector();
}


// Called every frame
void UAWEnvironmentSteeringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	BuildEnvironmentPlane(XYEnvironmentPlane);

	YZEnvironmentPlane.Mode = 2;
	BuildEnvironmentPlane(YZEnvironmentPlane);

	XZEnvironmentPlane.Mode = 3;
	BuildEnvironmentPlane(XZEnvironmentPlane);
	// ...
}

