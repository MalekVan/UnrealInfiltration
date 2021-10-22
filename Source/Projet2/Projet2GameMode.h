// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "BotTargetPoint.h"
#include "SpawnerOfAI.h"
#include "GameFramework/GameMode.h"
#include "Projet2GameMode.generated.h"

class AGameHUD;
class ASpawnerOfAI;
class ABotTargetPoint;

UCLASS()
class AProjet2GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProjet2GameMode();

	void AddEnemy(AAICharacter* Enemy);
	void RemoveEnemy(AAICharacter* Enemy);

	void AddScore(int Value);
	void CheckForVictory();
	void Victory();
	void Defeat();
	void ShowMouseForClick();
	
	AGameHUD* GameHUD;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
	int NumberOfEnnemyMax ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
	int NumberOfEnnemySpawn ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
    int NumberOfFruitsSpawn ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="VariablesGame")
	int NumberOfFruitsMax ;

	ASpawnerOfAI* SpawnerIA;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "CollectibleToSpawn")
	TSubclassOf<ACollectible> CollectibleClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AIToSpawn")
	TSubclassOf<AAICharacter> AIClass;

	TArray<ABotTargetPoint*> TargetPoints;
	
	FTimerHandle TimerHandle;
	
	void MakeCheckForSpawn();
	void SpawnIA();
	void AddTargetPoint(ABotTargetPoint* TargetPoint);

protected:
	int CurrentScore = 0;
	int MaxScore = 5;

	TArray<AAICharacter*> AliveEnemies;
};