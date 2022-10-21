// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AWCheckpointComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOGFIGHTGAME_API UAWCheckpointComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAWCheckpointComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SortCheckpointArray();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	

	//Keeps track of the valid checkpoints in the game. Populated at BeginPlay, then updated when a checkpoint is reached. 
	TArray<class AAWCheckpointElement*> CheckpointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DirectionArrow;
	
};
