// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AICharacterTestP.h"
#include "GameFramework/GameMode.h"
#include "Projet2GameMode.generated.h"

UCLASS()
class AProjet2GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProjet2GameMode();
	
	void AddScore(int value);
	bool CheckForVictory();
	
	class AGameHUD* GameHUD;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
	int NumberOfEnnemyMax ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
	int NumberOfEnnemySpawn ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
    int NumberOfFruitsSpawn ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
	int NumberOfFruitsMax ;

	class ASpawnerOfIA* SpawnerIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "IAToSpawn")
	TSubclassOf<AAICharacterTestP> IAClass;

	
	
	void MakeCheckForSpawn();
	void SpawnIA();

protected:
	int CurrentScore = 0;
	int MaxScore = 5;
};