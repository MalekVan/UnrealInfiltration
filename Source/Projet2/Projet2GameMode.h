// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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

protected:
	int CurrentScore = 0;
	int MaxScore = 5;
};