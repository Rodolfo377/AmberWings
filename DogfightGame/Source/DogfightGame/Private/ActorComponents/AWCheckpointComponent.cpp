// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AWCheckpointComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelElements/AWCheckpointElement.h"

// Sets default values for this component's properties
UAWCheckpointComponent::UAWCheckpointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/* Feature Creep. DirectionArrow = CreateDefaultSubobject<UStaticMeshComponent>("DirectionArrow");*/
	// ...
}


// Called when the game starts
void UAWCheckpointComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ResultActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAWCheckpointElement::StaticClass(), ResultActors);
	for (AActor* CheckpointActor : ResultActors)
	{
		AAWCheckpointElement* CheckpointElement = Cast<AAWCheckpointElement>(CheckpointActor);
		if (IsValid(CheckpointElement))
		{
			CheckpointArray.Add(CheckpointElement);
		}
	}
	SortCheckpointArray();
	// ...
	
}

void UAWCheckpointComponent::SortCheckpointArray()
{
	if (CheckpointArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkpoint array is Empty"));
		return;
	}
	for (size_t IndexKey = 0; IndexKey < CheckpointArray.Num() - 1; IndexKey++)
	{
		int32 SmallestId = CheckpointArray[IndexKey]->CheckpointUniqueID;
		int32 SmallestArrayIndex = IndexKey;
		for (size_t SmallestCandidateIndex = IndexKey + 1; SmallestCandidateIndex < CheckpointArray.Num(); SmallestCandidateIndex++)
		{
			if (SmallestId > CheckpointArray[SmallestCandidateIndex]->CheckpointUniqueID)
			{
				SmallestId = CheckpointArray[SmallestCandidateIndex]->CheckpointUniqueID;
				SmallestArrayIndex = SmallestCandidateIndex;
			}
		}
		CheckpointArray.Swap(IndexKey, SmallestArrayIndex);
	}
	CheckpointArray[0]->SetActorHiddenInGame(false);
	for (int i = 1; i < CheckpointArray.Num(); i++)
	{
		CheckpointArray[i]->SetActorHiddenInGame(true);
	}

	//debug printing
	for (AAWCheckpointElement* Checkpoint : CheckpointArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkpoint : %d"), Checkpoint->CheckpointUniqueID);
	}
}


// Called every frame
void UAWCheckpointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CheckpointArray.Num() > 0)
	{
		FVector ToTarget = CheckpointArray[0]->GetActorLocation() - GetOwner()->GetActorLocation();
		/* feature creep if (IsValid(DirectionArrow))
		{
			DirectionArrow->SetWorldRotation(FRotator(ToTarget.X, ToTarget.Y, ToTarget.Z) + FRotator(0, -90, 0));
			DirectionArrow->SetWorldLocation(GetOwner()->GetActorLocation());
		}*/
	}
	// ...
}

