// Fill out your copyright notice in the Description page of Project Settings.


#include "Ladder.h"

#include "Projet2Character.h"
#include "GameFramework/Character.h"

ALadder::ALadder()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

void ALadder::Interact(ACharacter* owner)
{
	ClimbLadder(owner);
}

void ALadder::ClimbLadder(ACharacter* owner)
{
	float DistanceToTop = AProjet2Character::GetDistanceBetweenVectors(owner->GetActorLocation(), HigherPosition);
	float DistanceToBottom = AProjet2Character::GetDistanceBetweenVectors(owner->GetActorLocation(), LowerPosition);

	if(DistanceToTop > DistanceToBottom)
	{
		owner->SetActorLocation(HigherPosition);
	} else
	{
		owner->SetActorLocation(LowerPosition);
	}
}