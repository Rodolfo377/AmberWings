// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AWEnvironmentSteeringComponent.generated.h"

USTRUCT(BlueprintType)
struct FAWEnvironmentPlane
{
	GENERATED_BODY()

	FAWEnvironmentPlane(){}
	
	//Mode will be 1, 2 or 3. For XY, YZand XZ respectively.
	UPROPERTY()
	int32 Mode = 1;
	//radial is each direction to be considered by the flying unit on a 360 degree basis. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering")
	int TotalRadials = 16;

	//Maps an index to its interest, represented by a vector in each radial direction.
	UPROPERTY()
	TMap<int32, FVector> InterestPlane;
	//Maps an index to its danger, represented by a vector in each radial direction.
	UPROPERTY()
	TMap<int32, FVector> DangerPlane;
	//Maps an index to its Sum (Interest - Danger), represented by a vector in each radial direction.
	UPROPERTY()
	TMap<int32, FVector> SumPlane;


	//Represents the most desired direction to move to considering interesting and dangerous elements on this environment plane. 
	UPROPERTY()
	FVector ResultPlaneDirection = FVector(0);
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOGFIGHTGAME_API UAWEnvironmentSteeringComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAWEnvironmentSteeringComponent();

	// Called when the game starts 
	void Init();

	// Called every frame
	void Update(float DeltaTime);
	
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:	

	//Build the radial vectors around the owner pawn, in the defined Plane. 
	UFUNCTION()
	void BuildEnvironmentPlane(FAWEnvironmentPlane& Plane);
	//Calculate the map corresponding to the GameplayTagContainer (Interest or Danger tag group).
	UFUNCTION()
	void ProcessEnvironmentPlaneMap(FAWEnvironmentPlane& EnvironmentPlane, const FGameplayTagContainer& Tags);

	UFUNCTION()
	void ProcessEnvironmentPlaneInterestMap(FAWEnvironmentPlane& EnvironmentPlane);

	UFUNCTION()
	void ProcessEnvironmentPlaneDangerMap(FAWEnvironmentPlane& EnvironmentPlane);
		
	//Determine the result for each map plane. 
	UFUNCTION()
	FVector GenerateEnvironmentPlaneMapResult(FAWEnvironmentPlane& EnvironmentPlane);
	//Calculate Result vector from all the environment plane calculations.
	UFUNCTION()
	FVector CalculateEnviromentSteeringVector();
public:	
	UPROPERTY()
	FAWEnvironmentPlane XYEnvironmentPlane;
	UPROPERTY()
	FAWEnvironmentPlane YZEnvironmentPlane;
	UPROPERTY()
	FAWEnvironmentPlane XZEnvironmentPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Interest")
	FGameplayTagContainer InterestElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Danger")
	FGameplayTagContainer DangerElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Movement")
	float ESTurningRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Interest")
	float InterestThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Danger")
	float DangerThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Debug")
	bool bDebugLogEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Debug")
	bool bDebugDrawEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Danger", meta = (ClampMin = "0.0"))
	float DangerRaycastLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Steering|Danger", meta = (ClampMin = "0.0"))
	float DangerWeight;
protected:
	UPROPERTY()
	class AAWFlightController* OwnerController;
	UPROPERTY()
	class AAWPlanePawn* OwnerActor;
		
};
