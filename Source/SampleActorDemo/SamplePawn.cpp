// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Bullet.h"
#include "Target.h"

// Sets default values
ASamplePawn::ASamplePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Statis Mesh");
	SetRootComponent(StaticMesh);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(StaticMesh);
	SpringArm->TargetArmLength = 500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(StaticMesh);
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void ASamplePawn::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ASamplePawn::OnHit);
}

void ASamplePawn::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if we collided with a Target
	if (ATarget* target = Cast<ATarget>(OtherActor))
	{
		OnTargetCollided.Broadcast(target);
		target->Destroy();
	}
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

void ASamplePawn::Shoot()
{
	if (!BulletClass) return;

	// Spawn the bullet
	FActorSpawnParameters spawnPrams;
	spawnPrams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnPrams.bNoFail = true;
	// Specify that it (the bullet) was spawn from this actor
	spawnPrams.Owner = this;
	// Specify who is source of the damage
	spawnPrams.Instigator = this;

	FTransform transform;
	transform.SetLocation(GetActorForwardVector() * BulletSpawnOffset + GetActorLocation());
	transform.SetRotation(GetActorQuat());
	transform.SetScale3D(FVector(1.0f));

	GetWorld()->SpawnActor<ABullet>(BulletClass, transform, spawnPrams);
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

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASamplePawn::Shoot);
}

