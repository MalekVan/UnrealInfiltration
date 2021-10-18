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

	void AddEnemy(AAICharacterTestP* Enemy);
	void RemoveEnemy(AAICharacterTestP* Enemy);

	void AddScore(int value);
	void CheckForVictory();
	void Victory();
	void Defeat();
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "CollectibleToSpawn")
	TSubclassOf<ACollectible> CollectibleClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "IAToSpawn")
	TSubclassOf<AAICharacterTestP> IAClass;

	TArray<ABotTargetPointTestP*> TargetPoints;
	
	FTimerHandle timerhandle;
	
	void MakeCheckForSpawn();
	void SpawnIA();
	void AddTargetPoint(ABotTargetPointTestP* TargetPoint);

protected:
	int CurrentScore = 0;
	int MaxScore = 5;

	TArray<AAICharacterTestP*> AliveEnemies;
};