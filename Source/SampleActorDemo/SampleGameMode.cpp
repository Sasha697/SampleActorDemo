// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleGameMode.h"

ASampleGameMode::ASampleGameMode()
{
	PointsToWin = 5;
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