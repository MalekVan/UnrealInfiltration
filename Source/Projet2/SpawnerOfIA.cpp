// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerOfIA.h"
#include "Projet2GameMode.h"
#include "AICharacterTestP.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnerOfIA::ASpawnerOfIA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
 
	BoxCollision -> OnComponentBeginOverlap.AddDynamic(this, &ASpawnerOfIA::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void ASpawnerOfIA::BeginPlay()
{
	Super::BeginPlay();
	AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	Gamemode->SpawnerIA = this;
	Gamemode->MakeCheckForSpawn();
}

void ASpawnerOfIA::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICharacterTestP* charaIA = Cast<AAICharacterTestP>(OtherActor);
	if (charaIA != nullptr)
	{
		if (charaIA->GoBackToZone == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("GO BACK TO ZONE"));
			charaIA->Destroy();
			AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
			Gamemode->NumberOfEnnemySpawn--;
			Gamemode->MakeCheckForSpawn();
		}
	}
}

// Called every frame
void ASpawnerOfIA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

