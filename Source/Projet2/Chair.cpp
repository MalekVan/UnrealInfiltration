// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"

#include "Projet2Character.h"

AChair::AChair()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

void AChair::Interact(ACharacter* owner)
{
	SitOnChair(owner);
}

void AChair::SitOnChair(ACharacter* owner)
{
	UE_LOG(LogTemp, Warning, TEXT("SIT"));
	AProjet2Character* player = Cast<AProjet2Character>(owner);

	FVector PlayerLocation = owner->GetActorLocation();
	FRotator PlayerRotation = owner->GetActorRotation();
	FRotator EndRotation = FRotator(0,150,0);
	
	if(player->AnimInstanceOfSkeletalMesh->IsSitting)
	{
		player->SetActorEnableCollision(true);		
		player->AnimInstanceOfSkeletalMesh->IsSitting = false;
	} else
	{
		player->AnimInstanceOfSkeletalMesh->IsSitting = true;
		player->SetActorEnableCollision(false);
		
		for (int i=0; i<=100; i++)
		{
			owner->SetActorLocation(FMath::Lerp(PlayerLocation, SittingPosition, i/100));
			owner->SetActorRotation(FMath::Lerp(PlayerRotation, EndRotation, i/100));		
		}
	}	
}