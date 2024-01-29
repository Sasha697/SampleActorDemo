// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASamplePawn::ASamplePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Statis Mesh");
	SetRootComponent(StaticMesh);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(StaticMesh);
	Camera->SetRelativeLocation(FVector(-500.0f, 0, 0));

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void ASamplePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASamplePawn::MoveForward(float scale)
{
	Movement->AddInputVector(GetActorForwardVector() * scale);
}

void ASamplePawn::MoveRight(float scale)
{
	Movement->AddInputVector(GetActorRightVector() * scale);
}

void ASamplePawn::Turn(float scale)
{
	AddControllerYawInput(scale);
}

void ASamplePawn::LookUp(float scale)
{
	AddControllerPitchInput(scale);
}

// Called every frame
void ASamplePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASamplePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASamplePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASamplePawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASamplePawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASamplePawn::LookUp);
}

