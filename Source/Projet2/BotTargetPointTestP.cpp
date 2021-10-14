// Fill out your copyright notice in the Description page of Project Settings.


#include "BotTargetPointTestP.h"

#include "AICharacterTestP.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ABotTargetPointTestP::ABotTargetPointTestP()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABotTargetPointTestP::OnBoxBeginOverlap);
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetRelativeLocation(FVector(0.0,.0,.0));

	//a voir avec Etienne
	//SocleMesh  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SocleMesh"));
	//SocleMesh->SetupAttachment(RootComponent);
	
}

void ABotTargetPointTestP::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
