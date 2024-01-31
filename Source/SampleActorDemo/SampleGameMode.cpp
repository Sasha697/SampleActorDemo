// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleGameMode.h"
#include "SamplePawn.h"

ASampleGameMode::ASampleGameMode()
{
	PointsToWin = 5;
	CurrentPoints = 0;
}

void ASampleGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ASamplePawn* pawn = Cast<ASamplePawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		// Listen to the event
		pawn->OnTargetCollided.AddDynamic(this, &ASampleGameMode::OnTargetCollided);
	}
}

void ASampleGameMode::OnTargetCollided(ATarget* target)
{
	DecreasePoints();
}

void ASampleGameMode::IncreasePoints()
{
	CurrentPoints++;
	OnPointsIncreased();
	if (CurrentPoints >= PointsToWin)
	{
		// We win 
		OnWin();
	}
}

void ASampleGameMode::DecreasePoints()
{
	CurrentPoints--;
	// Make sure it don't go below zero
	CurrentPoints = FMath::Max(CurrentPoints, 0);

	UE_LOG(LogTemp, Warning, TEXT("Points decreased %d"), CurrentPoints)

	OnPointsDecreased();
}


