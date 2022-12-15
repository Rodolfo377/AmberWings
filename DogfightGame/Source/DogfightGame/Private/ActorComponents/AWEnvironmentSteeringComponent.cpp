// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AWEnvironmentSteeringComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "ActorComponents/AWCheckpointComponent.h"
#include "Kismet/KismetSystemLibrary.h"
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
void UAWEnvironmentSteeringComponent::Init()
{
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
			FVector RadialPosition = OwnerActor->GetActorLocation() + QuaternionRotatedVector * 200.f;
			Plane.InterestPlane.Add(i, QuaternionRotatedVector);
			Plane.DangerPlane.Add(i, QuaternionRotatedVector);
			Plane.SumPlane.Add(i, QuaternionRotatedVector);

			//DrawDebugSphere(GetWorld(), RadialPosition, 20, 12, FColor::Blue, false, 1.0f, 0, 2.0f);
			//DrawDebugSphere(GetWorld(), OwnerActor, 20, 12, FColor::Red, false, 1.0f, 0, 2.0f);
		}
		
		for (TPair<int32, FVector>& RadialDirection : Plane.SumPlane)
		{
			/*if (bDebugDrawEnabled)
			{
				DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + 200.0f*RadialDirection.Value,
					FColor::Blue, false, -1, 0, 5);
			}*/

			/*if (bDebugLogEnabled)
			{
				UE_LOG(LogTemp, Warning, TEXT(" Radial %d: (%f, %f, %f) "), RadialDirection.Key,
					(RadialDirection.Value).X,
					(RadialDirection.Value).Y,
					OwnerActor->GetActorLocation().Z);
			}*/
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
			FVector RadialPosition = OwnerActor->GetActorLocation() + QuaternionRotatedVector * 200.0f;
			Plane.InterestPlane.Add(i, QuaternionRotatedVector);
			Plane.DangerPlane.Add(i, QuaternionRotatedVector);
			Plane.SumPlane.Add(i, QuaternionRotatedVector);
		}

		for (TPair<int32, FVector>& RadialDirection : Plane.SumPlane)
		{
			/*if (bDebugDrawEnabled)
			{
				DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + 200.0f * RadialDirection.Value,
					FColor::Blue, false, -1, 0, 5);
			}*/

			/*if (bDebugLogEnabled)
			{
				UE_LOG(LogTemp, Warning, TEXT(" Radial %d: (%f, %f, %f) "), RadialDirection.Key,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).X,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).Y,
					OwnerActor->GetActorLocation().Z);
			}*/
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
			Plane.DangerPlane.Add(i, QuaternionRotatedVector);
			Plane.SumPlane.Add(i, QuaternionRotatedVector);
		}

		for (TPair<int32, FVector>& RadialDirection : Plane.SumPlane)
		{
			/*if (bDebugDrawEnabled)
			{
				DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + 200.0f * RadialDirection.Value,
					FColor::Blue, false, -1, 0, 5);
			}*/

			/*if (bDebugLogEnabled)
			{
				UE_LOG(LogTemp, Warning, TEXT(" Radial %d: (%f, %f, %f) "), RadialDirection.Key,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).X,
					(OwnerActor->GetActorLocation() + RadialDirection.Value * 5.0f).Y,
					OwnerActor->GetActorLocation().Z);
			}*/
		}
	}
}


void UAWEnvironmentSteeringComponent::ProcessEnvironmentPlaneMap(FAWEnvironmentPlane& EnvironmentPlane, const FGameplayTagContainer& Tags)
{

}

void UAWEnvironmentSteeringComponent::ProcessEnvironmentPlaneInterestMap(FAWEnvironmentPlane& EnvironmentPlane)
{
	UAWCheckpointComponent* CheckpointComponent = Cast<UAWCheckpointComponent> (OwnerActor->GetComponentByClass(UAWCheckpointComponent::StaticClass()));
	FVector NextCheckpoint = CheckpointComponent->ReturnNextCheckpointsLocation();

	

	for (TPair<int32, FVector>& RadialDirection : EnvironmentPlane.InterestPlane)
	{
		FVector Dist = NextCheckpoint - OwnerActor->GetActorLocation();
		float DotProduct = FVector::DotProduct(Dist.GetSafeNormal(), RadialDirection.Value.GetSafeNormal());
		FColor DebugLineColor = FColor::Green;
		if (DotProduct > 0)
		{
			//DebugLineColor = FColor::Green;
			RadialDirection.Value +=  DotProduct * RadialDirection.Value;
			
		}
		if (bDebugDrawEnabled)
		{
			/*DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(),
				OwnerActor->GetActorLocation() + 200.0f*RadialDirection.Value,
				DebugLineColor, false, -1, 0, 5);*/
		}
	}
}

void UAWEnvironmentSteeringComponent::ProcessEnvironmentPlaneDangerMap(FAWEnvironmentPlane& EnvironmentPlane)
{
	for (TPair<int32, FVector>& RadialDirection : EnvironmentPlane.DangerPlane)
	{
		FHitResult OutHit;
		FVector Start = OwnerActor->GetActorLocation();
		FVector End = OwnerActor->GetActorLocation() + (DangerRaycastLength * RadialDirection.Value);
		FCollisionQueryParams CollisionParams;

		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_WorldStatic);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(OwnerActor);

		CollisionParams.AddIgnoredActor(OwnerActor);
		UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(),
			Start,
			End,
			200.0f,
			ObjectTypesArray,
			false,
			IgnoredActors,
			EDrawDebugTrace::None,
			OutHit,
			true);

		//DrawDebugLine(OwnerActor->GetWorld(), Start, End, FColor::Red, false, 0.5f, 0, 2.0f);
		//OwnerActor->GetWorld()->Trace(OutHit, Start, End, ECollisionChannel::ECC_WorldStatic, CollisionParams);

		if (OutHit.bBlockingHit)
		{
			FVector Dist = OutHit.ImpactPoint - OwnerActor->GetActorLocation();
			float DotProduct = FVector::DotProduct(Dist.GetSafeNormal(), RadialDirection.Value.GetSafeNormal());
			
			if (DotProduct > 0)
			{
				RadialDirection.Value += DangerWeight * DotProduct * RadialDirection.Value;
				DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), OwnerActor->GetActorLocation() + 200.0f * RadialDirection.Value,
					FColor::Red, false, -1, 0, 5);
			}		
		}
	}
}

FVector UAWEnvironmentSteeringComponent::GenerateEnvironmentPlaneMapResult(FAWEnvironmentPlane& EnvironmentPlane)
{
	FVector Result = FVector(0);

	for (TPair<int32, FVector>& RadialDirection : EnvironmentPlane.SumPlane)
	{
		int index = RadialDirection.Key;

		/*if (EnvironmentPlane.DangerPlane[index].Size() > DangerThreshold ||
			EnvironmentPlane.InterestPlane[index].Size() < InterestThreshold)
		{
			RadialDirection.Value *= 0;
		}*/
		//...


		if (EnvironmentPlane.InterestPlane[index].Size() - EnvironmentPlane.DangerPlane[index].Size() < 0)
		{
			EnvironmentPlane.SumPlane[index] = FVector(0);
			DrawDebugLine(GetWorld(), 
				OwnerActor->GetActorLocation(), 
				OwnerActor->GetActorLocation() + EnvironmentPlane.DangerPlane[index],
				FColor::Black, 
				false, 
				0.5f, 
				0, 
				15);

			continue;
		}		

		EnvironmentPlane.SumPlane[index] = EnvironmentPlane.InterestPlane[index] - EnvironmentPlane.DangerPlane[index];

		if (EnvironmentPlane.SumPlane[index].SizeSquared() > Result.SizeSquared())
		{
			Result = EnvironmentPlane.SumPlane[index];
		}

		if (bDebugDrawEnabled)
		{
			DrawDebugLine(GetWorld(),
				OwnerActor->GetActorLocation(),
				OwnerActor->GetActorLocation() + 200.0f * EnvironmentPlane.SumPlane[index],
				FColor::Blue, false, 0.1f, 0, 5);
		}
	}
	//...
	/*if (bDebugDrawEnabled)
	{
		DrawDebugLine(GetWorld(), OwnerActor->GetActorLocation(), Result, FColor::Green, false, -1, 0, 5);
	}*/

	return Result;
}

FVector UAWEnvironmentSteeringComponent::CalculateEnviromentSteeringVector()
{
	return FVector();
}


void UAWEnvironmentSteeringComponent::Update(float DeltaTime)
{
	BuildEnvironmentPlane(XYEnvironmentPlane);
	ProcessEnvironmentPlaneInterestMap(XYEnvironmentPlane);
	ProcessEnvironmentPlaneDangerMap(XYEnvironmentPlane);

	FVector XYResult = GenerateEnvironmentPlaneMapResult(XYEnvironmentPlane);

	YZEnvironmentPlane.Mode = 2;
	BuildEnvironmentPlane(YZEnvironmentPlane);
	ProcessEnvironmentPlaneInterestMap(YZEnvironmentPlane);
	ProcessEnvironmentPlaneDangerMap(YZEnvironmentPlane);
	FVector YZResult = GenerateEnvironmentPlaneMapResult(YZEnvironmentPlane);

	XZEnvironmentPlane.Mode = 3;
	BuildEnvironmentPlane(XZEnvironmentPlane);
	ProcessEnvironmentPlaneInterestMap(XZEnvironmentPlane);
	ProcessEnvironmentPlaneDangerMap(XZEnvironmentPlane);

	FVector XZResult = GenerateEnvironmentPlaneMapResult(XZEnvironmentPlane);

	FVector SumEnvironmentSteering = XYResult + YZResult + XZResult;

	OwnerActor->SetActorRotation(FMath::RInterpTo(OwnerActor->GetActorRotation(),
		SumEnvironmentSteering.Rotation(),
		DeltaTime,
		ESTurningRate));

	if (bDebugDrawEnabled)
	{
		DrawDebugLine(GetWorld(),
			OwnerActor->GetActorLocation(),
			(OwnerActor->GetActorLocation() + 200 * SumEnvironmentSteering),
			FColor::Purple,
			false,
			-1,
			0,
			25);
	}
}

