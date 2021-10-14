// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AICharacterTestP.h"
#include "GameFramework/GameModeBase.h"
#include "Projet2GameMode.generated.h"

UCLASS(minimalapi)
class AProjet2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjet2GameMode();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="VariablesGame")
	int NumberOfEnnemyMax = 2;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="VariablesGame")
	int NumberOfEnnemySpawn = 0;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="VariablesGame")
    int NumberOfFruitsSpawn = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="VariablesGame")
	int NumberOfFruitsMax = 5;

	class ASpawnerOfIA* SpawnerIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "IAToSpawn")
	TSubclassOf<AAICharacterTestP> IAClass;
	
	void MakeCheckForSpawn();
	void SpawnIA();
};



