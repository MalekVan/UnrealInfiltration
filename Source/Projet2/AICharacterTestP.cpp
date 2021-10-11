// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterTestP.h"

// Sets default values
AAICharacterTestP::AAICharacterTestP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacterTestP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacterTestP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacterTestP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

