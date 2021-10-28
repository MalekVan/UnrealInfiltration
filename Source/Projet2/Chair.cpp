// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"
#include "Components/CapsuleComponent.h"
#include "Projet2Character.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

AChair::AChair()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

void AChair::Interact(ACharacter* Player)
{
	SitOnChair(Player);
}

void AChair::SitOnChair(ACharacter* Player)
{
	AProjet2Character* PlayerCharacter = Cast<AProjet2Character>(Player);

	if(!PlayerCharacter->LevelChair)
	{
		PlayerCharacter->LevelChair = this;
	}
	
	FVector PlayerLocation = Player->GetActorLocation();
	FRotator PlayerRotation = Player->GetActorRotation();
	FRotator EndRotation = FRotator(0,150,0);
	
	if(PlayerCharacter->AnimInstanceOfSkeletalMesh->bIsSitting)
	{
		PlayerCharacter->SetActorLocation(GetActorLocation() + GetActorRightVector() * 200 + FVector(0,0,60));
		PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		PlayerCharacter->AnimInstanceOfSkeletalMesh->bIsSitting = false;
		PlayerCharacter->bCanMove = true;
		PlayerCharacter->GetController()->SetIgnoreLookInput(false);
	} else
	{
		float Distance = -200.f;
		
		PlayerCharacter->AnimInstanceOfSkeletalMesh->bIsSitting = true;
		PlayerCharacter->SetActorEnableCollision(false);
		PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		
		PlayerCharacter->bCanMove = false;
		for (int i=0; i<=100; i++)
		{
			Player->SetActorLocation(FMath::Lerp(PlayerLocation, SittingPosition, i/100));
			Player->SetActorRotation(FMath::Lerp(PlayerRotation, EndRotation, i/100));		
		}
		
		PlayerCharacter->GetFollowCamera()->SetWorldLocation(PlayerLocation + PlayerCharacter->GetActorForwardVector() * Distance + FVector(0,0,100));
		PlayerCharacter->GetController()->SetIgnoreLookInput(true);
	}	
}