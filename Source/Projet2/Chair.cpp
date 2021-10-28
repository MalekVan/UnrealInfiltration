// Fill out your copyright notice in the Description page of Project Settings.

#include "Chair.h"
#include "Projet2Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AChair::AChair()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

void AChair::Interact(ACharacter* Player)
{
	AProjet2Character* PlayerCharacter = Cast<AProjet2Character>(Player);
	
	if(PlayerCharacter == nullptr) return;
	
	if(PlayerCharacter->AnimInstanceOfSkeletalMesh->bIsSitting)
	{
		GetUpFromChair(PlayerCharacter);
	} else
	{
		SitOnChair(PlayerCharacter);
	}
}

void AChair::SitOnChair(AProjet2Character* Player)
{
	if(!Player->LevelChair)
	{
		Player->LevelChair = this;
	}

	OldCameraPos = Player->GetFollowCamera()->GetComponentLocation();
	OldCameraRot = Player->GetFollowCamera()->GetComponentRotation();
	
	FVector PlayerLocation = Player->GetActorLocation();
	FRotator PlayerRotation = Player->GetActorRotation();
	FRotator EndRotation = FRotator(0,150,0);
	
	if(!Player->AnimInstanceOfSkeletalMesh->bIsSitting)
	{
		float Distance = 200.f;
		
		Player->bCanMove = false;
		Player->AnimInstanceOfSkeletalMesh->bIsSitting = true;
		Player->SetActorEnableCollision(false);
		
		for (int i=0; i<=100; i++)
		{
			Player->SetActorLocation(FMath::Lerp(PlayerLocation, SittingPosition, i/100));
			Player->SetActorRotation(FMath::Lerp(PlayerRotation, EndRotation, i/100));		
		}
		
		FRotator CameraRotation = Player->GetTransform().InverseTransformPosition(Player->GetActorLocation()).Rotation();
		CameraRotation.Yaw -= 180;

		Player->GetCameraBoom()->SetRelativeRotation(CameraRotation);
		Player->GetCameraBoom()->bUsePawnControlRotation = false;

		Player->GetController()->SetIgnoreLookInput(true);
	}	
}

void AChair::GetUpFromChair(AProjet2Character* Player)
{
	if(Player->AnimInstanceOfSkeletalMesh->bIsSitting)
	{
		Player->SetActorLocation(GetActorLocation() + GetActorRightVector() * 50 + FVector(0,0,60));
		Player->SetActorEnableCollision(true);
		
		Player->GetCameraBoom()->bUsePawnControlRotation = true;
		
		Player->AnimInstanceOfSkeletalMesh->bIsSitting = false;
		Player->bCanMove = true;
		Player->GetController()->SetIgnoreLookInput(false);
		Player->LevelChair = nullptr;
	}
}