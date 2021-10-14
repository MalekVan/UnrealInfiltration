// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projet2GameMode.h"
#include "GameHUD.h"
#include "AICharacterTestP.h"
#include "MyAIControllerTestP.h"
#include "SpawnerOfIA.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"

AProjet2GameMode::AProjet2GameMode()
{
	NumberOfEnnemyMax = 1;
	NumberOfEnnemySpawn = 0;
	NumberOfFruitsMax = 5;
	NumberOfFruitsSpawn = 0;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AProjet2GameMode::AddScore(int Value)
{	
	CurrentScore += Value;

	GameHUD->UpdateProgressBar(CurrentScore, MaxScore);
	
	CheckForVictory();
}

bool AProjet2GameMode::CheckForVictory()
{
	return CurrentScore >= MaxScore;
}

void AProjet2GameMode::MakeCheckForSpawn()
{
	if (NumberOfEnnemySpawn < NumberOfEnnemyMax)
	{
		SpawnIA();
		NumberOfEnnemySpawn++;
		MakeCheckForSpawn();
	}	
}

void AProjet2GameMode::SpawnIA()
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	AAICharacterTestP* refCharSpawn=  GetWorld()->SpawnActor<AAICharacterTestP>(IAClass, SpawnerIA->GetActorLocation(), Rotation, SpawnInfo);
	AMyAIControllerTestP* refController = nullptr;
	if (refCharSpawn)
	{
		refController = Cast<AMyAIControllerTestP>(refCharSpawn->GetController());
	}
	if (refController)
	{
		refController->GetBlackboardComp()->SetValueAsObject("BasePosition", SpawnerIA);
	}

}
