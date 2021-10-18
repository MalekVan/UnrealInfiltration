// Fill out your copyright notice in the Description page of Project Settings.


#include "BotTargetPointTestP.h"

#include "AICharacterTestP.h"
#include "Projet2GameMode.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABotTargetPointTestP::ABotTargetPointTestP()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetRelativeLocation(FVector(0.0,.0,.0));

	//ETIENNE
	SocleMesh  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SocleMesh"));
	SocleMesh->SetupAttachment(RootComponent);	
	SocleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABotTargetPointTestP::BeginPlay()
{
	Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode())->AddTargetPoint(this);
}

void ABotTargetPointTestP::SpawnFruitOnPoint()
{
	AProjet2GameMode* GameMode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ACollectible>(GameMode->CollectibleClass, GetActorLocation(), FRotator(0.0,0.0,0.0), SpawnInfo);
}