// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacterTestP.h"

#include "AnimClassForIA.h"
#include "Projet2GameMode.h"
#include "Collectible.h"
#include "Projet2Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIControllerTestP.h"
#include "Components/CapsuleComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAICharacterTestP::AAICharacterTestP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAICharacterTestP::OnPerceptionUpdatedDelegate);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAICharacterTestP::OnStaticMeshBeginOverlap);
}

// Called when the game starts or when spawned
void AAICharacterTestP::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAICharacterTestP::OnPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* BlackboardComponent = Cast<AMyAIControllerTestP>(GetController())->GetBlackboardComp();

	AProjet2Character* chara = Cast<AProjet2Character>(Actor);
	
	if (BlackboardComponent && chara)
	{		
		BlackboardComponent->SetValueAsVector(TEXT("JoueurPos"), Stimulus.StimulusLocation);

		bool bNewValue = !BlackboardComponent->GetValueAsBool(TEXT("DetectPlayer"));
		BlackboardComponent->SetValueAsBool(TEXT("DetectPlayer"), bNewValue);
	}
}

void AAICharacterTestP::OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	if(AProjet2Character* Player = Cast<AProjet2Character>(OtherActor))
	{
		UAnimClassForIA* animclass = Cast<UAnimClassForIA>(GetMesh()->GetAnimInstance());
		animclass->bWon = true;
		Cast<AProjet2GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->Defeat();		
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
	UAnimClassForIA* animclass = Cast<UAnimClassForIA>(GetMesh()->GetAnimInstance());
	animclass->bIsCarry = true;
}

ACollectible* AAICharacterTestP::CreateFruit()
{
	AProjet2GameMode* GameMode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	ACollectible* fruitt =  GetWorld()->SpawnActor<ACollectible>(GameMode->CollectibleClass, this->GetActorLocation(), Rotation, SpawnInfo);

	AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	Gamemode->NumberOfFruitsSpawn ++;
	return fruitt;
}

void AAICharacterTestP::PutDownAFruit()
{
	if (Fruit)
	{
		Fruit->Drop();
		UAnimClassForIA* animclass = Cast<UAnimClassForIA>(GetMesh()->GetAnimInstance());
		animclass->bIsCarry = false;
		bGoBackToZone = true;
	}
}

