// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelElements/AWCheckpointElement.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Pawns/AWPlanePawn.h"
#include "ActorComponents/AWCheckpointComponent.h"

// Sets default values
AAWCheckpointElement::AAWCheckpointElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 100.0f;

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("My Sphere Component"));
	CollisionCapsule->InitCapsuleSize(50.0f, 100.0f);
	CollisionCapsule->SetCollisionProfileName("Trigger");
	RootComponent = CollisionCapsule;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAWCheckpointElement::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AAWCheckpointElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAWCheckpointElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAWCheckpointElement::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAWPlanePawn* CollisionPlane = Cast<AAWPlanePawn>(OtherActor);
	if (IsValid(CollisionPlane))
	{
		UAWCheckpointComponent* CheckpointComponent = Cast<UAWCheckpointComponent>(CollisionPlane->GetComponentByClass(UAWCheckpointComponent::StaticClass()));
		CheckpointComponent->CheckpointArray.RemoveSingle(this);
		CheckpointComponent->SortCheckpointArray();
		//Destroy();
		SetActorHiddenInGame(true);
		//TODO: Update Checkpoint Component array.
		//CheckpointComponent->CheckpointArray
	}
}

