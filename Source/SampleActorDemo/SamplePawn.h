// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SamplePawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetCollidedSignature, class ATarget*, Target);

UCLASS()
class SAMPLEACTORDEMO_API ASamplePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASamplePawn();

	UPROPERTY(BlueprintAssignable)
	FTargetCollidedSignature OnTargetCollided;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class TSubclassOf<class ABullet> BulletClass;

	// Distance between SamplePawn and the bullet that is spawning
	UPROPERTY(EditAnywhere)
	float BulletSpawnOffset;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// Input bindings
	void MoveForward(float scale);
	void MoveRight(float scale);
	void Turn(float scale);
	void LookUp(float scale);
	void Shoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
