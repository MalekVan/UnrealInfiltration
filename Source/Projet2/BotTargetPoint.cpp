// Fill out your copyright notice in the Description page of Project Settings.


#include "BotTargetPoint.h"

#include "AICharacter.h"
#include "Projet2GameMode.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABotTargetPoint::ABotTargetPoint()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetRelativeLocation(FVector(0.0,.0,.0));

	//ETIENNE
	SocleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SocleMesh"));
	SocleMesh->SetupAttachment(RootComponent);	
	SocleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABotTargetPoint::BeginPlay()
{
	Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode())->AddTargetPoint(this);
}

void ABotTargetPoint::SpawnFruitOnPoint()
{
	AProjet2GameMode* GameMode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ACollectible>(GameMode->CollectibleClass, GetActorLocation(), FRotator(0.0,0.0,0.0), SpawnInfo);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "point spawn at start :" + this->GetName());
	bFruitOnThisTargetPoint = true;
}