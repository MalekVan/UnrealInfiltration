// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

#include "Projet2Character.h"
#include "Projet2GameMode.h"

void AChest::Interact(ACharacter* Player)
{
	StoreFruit(Player);
}

void AChest::StoreFruit(ACharacter* Actor)
{
	if(AProjet2Character* Player = Cast<AProjet2Character>(Actor))
	{
		if(Player->bIsCarry)
		{
			Player->HoldedCollectible->Destroy();
			Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode())->AddScore(1);
			Player->HoldedCollectible = nullptr;
			Player->bIsCarry = false;
			Player->AnimInstanceOfSkeletalMesh->IsCarry = Player->bIsCarry;
		}
	}
}
