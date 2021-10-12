// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectible.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AThisObject = this;
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UStaticMeshComponent*> StaticComps;
	GetComponents<UStaticMeshComponent>(StaticComps);
	StaticMesh = *StaticComps.GetData();
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectible::Interact()
{
	Pickup();
}

void ACollectible::Pickup()
{	
	UE_LOG(LogClass, Log, TEXT("Interact with %s"), *GetName());
	if(!bIsCarried)
	{
		
	}
}
