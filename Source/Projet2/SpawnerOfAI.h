// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerOfAI.generated.h"
class ABotTargetPoint;
UCLASS()
class PROJET2_API ASpawnerOfAI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerOfAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void FirstTcheckForSpawn();

	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle2;
	void IncreaseNumberMaxOfAI();
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};


