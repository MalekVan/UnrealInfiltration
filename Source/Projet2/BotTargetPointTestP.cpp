// Fill out your copyright notice in the Description page of Project Settings.


#include "BotTargetPointTestP.h"

#include "AICharacterTestP.h"
#include "Components/BoxComponent.h"

ABotTargetPointTestP::ABotTargetPointTestP()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABotTargetPointTestP::OnBoxBeginOverlap);
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetRelativeLocation(FVector(0.0,.0,.0));
	
	//Recuperer le component car probleme quand on essaye de la créer
	TArray<UBoxComponent*> arraybox = TArray<UBoxComponent*>();
	GetComponents<UBoxComponent>(arraybox);
	if (arraybox.Num() > 0)
	{
		BoxCollision = arraybox[0];
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABotTargetPointTestP::OnBoxBeginOverlap);
	}
}

void ABotTargetPointTestP::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP SOMETHING"));
	if (AAICharacterTestP* IAchara = Cast<AAICharacterTestP>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP IA"));
		FruitOnThisTargetPoint=true;
		IAchara->PutDownAFruit();
	}
}
