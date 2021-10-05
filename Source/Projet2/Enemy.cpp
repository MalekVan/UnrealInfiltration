// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	target = nullptr;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController());
	if (AIController) {
		UE_LOG(LogTemp, Warning, TEXT("AIControllerInit"));
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::MoveToAPoint(FTransform goal)
{
	if (AIController) {
		UE_LOG(LogTemp, Warning, TEXT("OUI OUI Oui"));
		FAIMoveRequest moveRequest;
		moveRequest.SetGoalLocation(goal.GetLocation());
		moveRequest.SetAcceptanceRadius(0.25f);
		FNavPathSharedPtr NavPath;
		AIController->MoveTo(moveRequest, &NavPath);
	}
}

