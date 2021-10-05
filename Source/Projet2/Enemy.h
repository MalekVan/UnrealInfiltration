// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Enemy.generated.h"

UCLASS()
class PROJET2_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		AActor* target;
	// Sets default values for this character's properties
	AEnemy();
	class AAIController* AIController;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveToAPoint(FTransform goal);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
