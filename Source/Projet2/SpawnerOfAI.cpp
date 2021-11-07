// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerOfAI.h"
#include "Projet2GameMode.h"
#include "GameFramework/Actor.h"
#include "AICharacter.h"
#include "BotTargetPoint.h"

// Sets default values
ASpawnerOfAI::ASpawnerOfAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnerOfAI::BeginPlay()
{
	Super::BeginPlay();
	
	//Wait 2second before first spawn
	GetWorldTimerManager().SetTimer(TimerHandle2, this, &ASpawnerOfAI::FirstTcheckForSpawn, 2.0f, false);

	//After one minute, there is one more AI
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerOfAI::IncreaseNumberMaxOfAI, 60.0f, false);
}

void ASpawnerOfAI::FirstTcheckForSpawn()
{
	AProjet2GameMode* GameMode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SpawnerIA = this;
	GameMode->MakeCheckForSpawn();
}

// Called every frame
void ASpawnerOfAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnerOfAI::IncreaseNumberMaxOfAI()
{
	AProjet2GameMode* GameMode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	GameMode->NumberOfEnnemyMax++;
	GameMode->MakeCheckForSpawn();
}

