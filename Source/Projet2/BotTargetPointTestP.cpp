// Fill out your copyright notice in the Description page of Project Settings.


#include "BotTargetPointTestP.h"

#include "AICharacterTestP.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ABotTargetPointTestP::ABotTargetPointTestP()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetRelativeLocation(FVector(0.0,.0,.0));

	//ETIENNE
	//SocleMesh  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SocleMesh"));
	//SocleMesh->SetupAttachment(RootComponent);
}
