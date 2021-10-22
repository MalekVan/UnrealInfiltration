// Fill out your copyright notice in the Description page of Project Settings.


#include "Ladder.h"

#include "Projet2Character.h"
#include "GameFramework/Character.h"

ALadder::ALadder()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

void ALadder::Interact(ACharacter* Player)
{
	ClimbLadder(Player);
}

void ALadder::ClimbLadder(ACharacter* Player)
{
	float DistanceToTop = AProjet2Character::GetDistanceBetweenVectors(Player->GetActorLocation(), HigherPosition);
	float DistanceToBottom = AProjet2Character::GetDistanceBetweenVectors(Player->GetActorLocation(), LowerPosition);

	if(DistanceToTop > DistanceToBottom)
	{
		Player->SetActorLocation(HigherPosition);
	} else
	{
		Player->SetActorLocation(LowerPosition);
	}
}