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
	
	if (Plane.Mode == 1)
	{
		float deltaAngleDegrees = 360.0f / Plane.TotalRadials;		
		float deltaAngleRadians = deltaAngleDegrees * PI/180.0f;
		for (int i = 0; i < Plane.TotalRadials; i++)
		{
			float cosDelta = FMath::Cos(deltaAngleRadians * i);
			float sinDelta = FMath::Sin(deltaAngleRadians * i);

			FVector RotatedVector = FVector(OwnerActor->GetActorForwardVector().X * cosDelta - OwnerActor->GetActorForwardVector().Y * sinDelta,
				OwnerActor->GetActorForwardVector().X * sinDelta + OwnerActor->GetActorForwardVector().Y * cosDelta, 0);
			Plane.InterestPlane.Add(i, RotatedVector);
		}
		
			for (TPair<int32, FVector>& RadialDirection : Plane.InterestPlane)
			{
				if (bDebugDrawEnabled)
				{
					DrawDebugSphere(GetWorld(), OwnerActor->GetActorLocation() + RadialDirection.Value * 200.0f, 30, 6, FColor::Red, false, -1, 0, 5);
				}
				/*DrawDebugLine(GetWorld(),
					OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f, FColor::Green, false, 1.0f, 0, 5);*/
				//UE_LOG(LogTemp, Warning, TEXT(" Radial %d: (%f, %f, %f) "), RadialDirection.Key, RadialDirection.Value.X, RadialDirection.Value.Y, 0);
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
	// ...
}

