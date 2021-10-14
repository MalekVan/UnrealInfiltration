// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacterTestP.h"
#include "Projet2GameMode.h"
#include "Collectible.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIControllerTestP.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
AAICharacterTestP::AAICharacterTestP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAICharacterTestP::OnPerceptionUpdatedDelegate);
}

// Called when the game starts or when spawned
void AAICharacterTestP::BeginPlay()
{
	Super::BeginPlay();
	AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	
	if(Gamemode->NumberOfFruitsSpawn < Gamemode->NumberOfFruitsMax)
	{
		HaveFruit = true;
		//faire spawn le fruit dans le socket correspondant.
		AttachAFruitToSocket(CreateFruit());
	}
	else
	{
		HaveFruit = false;
	}
}

void AAICharacterTestP::OnPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("EVENT CALL, DETECT PLAYER"));

	UBlackboardComponent* BlackboardComponent = Cast<AMyAIControllerTestP>(GetController())->GetBlackboardComp();
	
	if (BlackboardComponent)
	{		
		BlackboardComponent->SetValueAsVector(TEXT("JoueurPos"), Stimulus.StimulusLocation);

		bool NewValue = !BlackboardComponent->GetValueAsBool(TEXT("DetectPlayer"));
		BlackboardComponent->SetValueAsBool(TEXT("DetectPlayer"), NewValue);
	}
}


// Called every frame
void AAICharacterTestP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAICharacterTestP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacterTestP::AttachAFruitToSocket(ACollectible* collectible)
{
	collectible->Pickup(this);
	Fruit = collectible;
}

ACollectible* AAICharacterTestP::CreateFruit()
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	ACollectible* fruitt =  GetWorld()->SpawnActor<ACollectible>(collectibleClass, this->GetActorLocation(), Rotation, SpawnInfo);
	return fruitt;
}

void AAICharacterTestP::PutDownAFruit()
{
	UE_LOG(LogTemp, Warning, TEXT("PUT DOWN A FRUIT"));
	if (Fruit)
	{
		Fruit->Drop();
		GoBackToZone = true;
		UBlackboardComponent* BlackboardComponent = Cast<AMyAIControllerTestP>(GetController())->GetBlackboardComp();
		BlackboardComponent->SetValueAsBool(TEXT("GoBackToBase"), true);
	}
}

