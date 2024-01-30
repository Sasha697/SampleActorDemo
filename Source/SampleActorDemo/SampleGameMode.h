// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SampleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEACTORDEMO_API ASampleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASampleGameMode();

	UFUNCTION(BlueprintCallable)
	void IncreasePoints();

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	int32 PointsToWin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Game Rules")
	int32 CurrentPoints;

protected:
	// BlueprintImplementableEvent shouldn't have any implementation
	UFUNCTION(BlueprintImplementableEvent)
	void OnPointsIncreased();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWin();
};
