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
	
	// Handles increasing of points and determining win condition
	void IncreasePoints();

	// Handles decreasing of points
	void DecreasePoints();

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	int32 PointsToWin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Game Rules")
	int32 CurrentPoints;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTargetCollided(class ATarget* target);

	// BlueprintImplementableEvent don't need any implementation
	UFUNCTION(BlueprintImplementableEvent)
	void OnPointsIncreased();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPointsDecreased();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWin();
};
