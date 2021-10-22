// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"

#include "AnimClassForAI.h"
#include "Projet2GameMode.h"
#include "Collectible.h"
#include "Projet2Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "Components/CapsuleComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAICharacter::OnPerceptionUpdatedDelegate);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnStaticMeshBeginOverlap);
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAICharacter::OnPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* BlackboardComponent = Cast<AMyAIController>(GetController())->GetBlackboardComp();

	AProjet2Character* Character = Cast<AProjet2Character>(Actor);
	UE_LOG(LogTemp, Warning, TEXT("Perception Update"));
	if (BlackboardComponent && Character)
	{		
		BlackboardComponent->SetValueAsVector(TEXT("PlayerPos"), Stimulus.StimulusLocation);
		UE_LOG(LogTemp, Warning, TEXT("DETECT PLAYER"));

		bool bNewValue = !BlackboardComponent->GetValueAsBool(TEXT("DetectPlayer"));
		BlackboardComponent->SetValueAsBool(TEXT("DetectPlayer"), bNewValue);
	}
}

void AAICharacter::OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	if(AProjet2Character* Player = Cast<AProjet2Character>(OtherActor))
	{
		UAnimClassForAI* AnimClass = Cast<UAnimClassForAI>(GetMesh()->GetAnimInstance());
		AnimClass->bWon = true;
		Cast<AProjet2GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->Defeat();		
	}
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::AttachAFruitToSocket(ACollectible* Collectible)
{
	Collectible->Pickup(this);
	Fruit = Collectible;
	UAnimClassForAI* AnimClass = Cast<UAnimClassForAI>(GetMesh()->GetAnimInstance());
	AnimClass->bIsCarry = true;
}

ACollectible* AAICharacter::CreateFruit()
{
	AProjet2GameMode* GameMode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	ACollectible* Collectible =  GetWorld()->SpawnActor<ACollectible>(GameMode->CollectibleClass, this->GetActorLocation(), Rotation, SpawnInfo);

	GameMode->NumberOfFruitsSpawn ++;
	return Collectible;
}

void AAICharacter::PutDownAFruit()
{
	if (Fruit)
	{
		Fruit->Drop();
		UAnimClassForAI* AnimClass = Cast<UAnimClassForAI>(GetMesh()->GetAnimInstance());
		AnimClass->bIsCarry = false;
		bGoBackToZone = true;
	}
}

