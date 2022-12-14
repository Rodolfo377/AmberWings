// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "AWCheckpointElement.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FCheckpointReached, FHitResult)

UCLASS()
class DOGFIGHTGAME_API AAWCheckpointElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAWCheckpointElement();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// declare collision component
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CollisionCapsule;

	// declare mesh component
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	float SphereRadius;

	FCheckpointReached CheckpointReachedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CheckpointUniqueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer InterestTags;
};
