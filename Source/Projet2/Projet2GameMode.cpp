// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projet2GameMode.h"
#include "GameHUD.h"
#include "AICharacter.h"
#include "AnimClassForAI.h"
#include "MyAIController.h"
#include "Projet2Character.h"
#include "SpawnerOfAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BotTargetPoint.h"

AProjet2GameMode::AProjet2GameMode()
{
	NumberOfEnnemyMax = 2;
	NumberOfEnnemySpawn = 0;
	NumberOfFruitsMax = 5;
	NumberOfFruitsSpawn = 0;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	AliveEnemies = TArray<AAICharacter*>();
	TargetPoints = TArray<ABotTargetPoint*>();
}

void AProjet2GameMode::AddScore(int Value)
{	
	CurrentScore += Value;

	GameHUD->UpdateProgressBar(CurrentScore, MaxScore);
	
	CheckForVictory();
}

void AProjet2GameMode::CheckForVictory()
{
	if(CurrentScore >= MaxScore)
		Victory();
}

void AProjet2GameMode::Victory()
{
	AProjet2Character* Character = Cast<AProjet2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Character->AnimInstanceOfSkeletalMesh->bWon = true;
	Character->bCanMove = false;

	TArray<AActor*> AllEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), AllEnemies);

	for (AActor* Enemy : AllEnemies)
	{
		if(AAICharacter* IAEnemy = Cast<AAICharacter>(Enemy))
		{
			Cast<UAnimClassForAI>(IAEnemy->GetMesh()->GetAnimInstance())->bLost = true;
			IAEnemy->GetCharacterMovement()->MaxWalkSpeed = 0.0;;
			IAEnemy->GetCharacterMovement()->Velocity = FVector(0.0,0.0,0.0);
			
			IAEnemy->PerceptionComponent->SetActive(false);
			IAEnemy->GetController()->UnPossess();
		}
	}

	GameHUD->DisplayVictoryMessage();
	Character->GetController()->SetIgnoreLookInput(true);
	ShowMouseForClick();
}

void AProjet2GameMode::Defeat()
{
	AProjet2Character* Character = Cast<AProjet2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Character->AnimInstanceOfSkeletalMesh->bLost = true;
	Character->bCanMove = false;
	
	TArray<AActor*> AllEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), AllEnemies);
	//TActorIterator<AAICharacterTestP> ActorItr = TActorIterator<AAICharacterTestP>(GetWorld());

	for (AActor* Enemy : AllEnemies)
	{
		if(AAICharacter* IAEnemy = Cast<AAICharacter>(Enemy))
		{			
			Cast<UAnimClassForAI>(IAEnemy->GetMesh()->GetAnimInstance())->bWon = true;
			IAEnemy->GetCharacterMovement()->MaxWalkSpeed = 0.0;;
			IAEnemy->GetCharacterMovement()->Velocity = FVector(0.0,0.0,0.0);

			IAEnemy->PerceptionComponent->SetActive(false);
			IAEnemy->GetController()->UnPossess();
		}
	}
	GameHUD->DisplayDeathMessage();
	Character->GetController()->SetIgnoreLookInput(true);
	ShowMouseForClick();
}

void AProjet2GameMode::ShowMouseForClick()
{
	APlayerController* MyController = Cast<APlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController());
 
	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;
}

void AProjet2GameMode::MakeCheckForSpawn()
{
	if (NumberOfEnnemySpawn < NumberOfEnnemyMax)
	{
		SpawnIA();
		NumberOfEnnemySpawn++;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjet2GameMode::MakeCheckForSpawn, 2.0f, false);
	}	
}

void AProjet2GameMode::SpawnIA()
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	AAICharacter* RefCharSpawn=  GetWorld()->SpawnActor<AAICharacter>(AIClass, SpawnerIA->GetActorLocation(), Rotation, SpawnInfo);
	AMyAIController* RefController = nullptr;
	if (RefCharSpawn)
	{
		RefController = Cast<AMyAIController>(RefCharSpawn->GetController());
	}
	if (RefController)
	{
		RefController->GetBlackboardComp()->SetValueAsObject("BasePosition", SpawnerIA);
	}
	AddEnemy(RefCharSpawn);
}

void AProjet2GameMode::AddEnemy(AAICharacter* Enemy)
{
	AliveEnemies.Add(Enemy);
}

void AProjet2GameMode::RemoveEnemy(AAICharacter* Enemy)
{
	AliveEnemies.Remove(Enemy);
}

void AProjet2GameMode::AddTargetPoint(ABotTargetPoint* TargetPoint)
{
	TargetPoints.Add(TargetPoint);

	if(TargetPoints.Num() == 9)
	{
		int RandomInt = FMath::RandRange(0, TargetPoints.Num()-1);
		TargetPoints[RandomInt]->SpawnFruitOnPoint();
	}
}
