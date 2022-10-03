// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/AWPlanePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAWPlanePawn::AAWPlanePawn():
	AirplaneMesh(nullptr),
	CapsuleComponent(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetEnableGravity(false);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CapsuleComponent);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//AirplaneMesh->SetupAttachment(Capsule);
}

// Called when the game starts or when spawned
void AAWPlanePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAWPlanePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DebugDraw)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + 200*GetActorForwardVector(), FColor::Emerald, false, 2, 0, 5);
	}
}

// Called to bind functionality to input
void AAWPlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

