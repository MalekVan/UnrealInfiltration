// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerOfIA.h"
#include "Projet2GameMode.h"
#include "GameFramework/Actor.h"
#include "AICharacterTestP.h"
#include "BotTargetPointTestP.h"

// Sets default values
ASpawnerOfIA::ASpawnerOfIA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnerOfIA::BeginPlay()
{
	Super::BeginPlay();

	int i = FMath::RandRange(0, Spawners.Num()-1);
	
	AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	Gamemode->SpawnerIA = this;
	Gamemode->MakeCheckForSpawn();

	//Apres une minute, on augmente le nombre d'IA de 1
	GetWorldTimerManager().SetTimer(timerhandle, this, &ASpawnerOfIA::IncreaseNumberMaxOfIA, 60.0f, false);
}

// Called every frame
void ASpawnerOfIA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnerOfIA::IncreaseNumberMaxOfIA()
{
	UE_LOG(LogTemp, Warning, TEXT("INCREASE ENNEMY NUMBER"));
	AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	Gamemode->NumberOfEnnemyMax ++;
	Gamemode->MakeCheckForSpawn();
}

