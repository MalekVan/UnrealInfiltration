// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projet2GameMode.h"
#include "GameHUD.h"
#include "AICharacterTestP.h"
#include "TimerManager.h"
#include "AnimClassForIA.h"
#include "MyAIControllerTestP.h"
#include "Projet2Character.h"
#include "SpawnerOfIA.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BotTargetPointTestP.h"

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

	AliveEnemies = TArray<AAICharacterTestP*>();
	TargetPoints = TArray<ABotTargetPointTestP*>();
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
	AProjet2Character* chara = Cast<AProjet2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	chara->AnimInstanceOfSkeletalMesh->bWon = true;
	chara->bCanMove = false;

	TArray<AActor*> AllEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacterTestP::StaticClass(), AllEnemies);
	//TActorIterator<AAICharacterTestP> ActorItr = TActorIterator<AAICharacterTestP>(GetWorld());

	for (AActor* Enemy : AllEnemies)
	{
		if(AAICharacterTestP* IAEnemy = Cast<AAICharacterTestP>(Enemy))
		{
			Cast<UAnimClassForIA>(IAEnemy->GetMesh()->GetAnimInstance())->bLost = true;
			IAEnemy->GetCharacterMovement()->MaxWalkSpeed = 0.0;;
			IAEnemy->GetCharacterMovement()->Velocity = FVector(0.0,0.0,0.0);
		}
	}

	GameHUD->DisplayVictoryMessage();
	chara->GetController()->SetIgnoreLookInput(true);
	ShowMouseForClick();
}

void AProjet2GameMode::Defeat()
{
	AProjet2Character* chara = Cast<AProjet2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	chara->AnimInstanceOfSkeletalMesh->bLost = true;
	chara->bCanMove = false;
	
	TArray<AActor*> AllEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacterTestP::StaticClass(), AllEnemies);
	//TActorIterator<AAICharacterTestP> ActorItr = TActorIterator<AAICharacterTestP>(GetWorld());

	for (AActor* Enemy : AllEnemies)
	{
		if(AAICharacterTestP* IAEnemy = Cast<AAICharacterTestP>(Enemy))
		{			
			Cast<UAnimClassForIA>(IAEnemy->GetMesh()->GetAnimInstance())->bWon = true;
			IAEnemy->GetCharacterMovement()->MaxWalkSpeed = 0.0;;
			IAEnemy->GetCharacterMovement()->Velocity = FVector(0.0,0.0,0.0);
		}
	}
	GameHUD->DisplayDeathMessage();
	chara->GetController()->SetIgnoreLookInput(true);
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
		MakeCheckForSpawn();
	}	
}

void AProjet2GameMode::SpawnIA()
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	AAICharacterTestP* refCharSpawn=  GetWorld()->SpawnActor<AAICharacterTestP>(IAClass, SpawnerIA->GetActorLocation(), Rotation, SpawnInfo);
	AMyAIControllerTestP* refController = nullptr;
	if (refCharSpawn)
	{
		refController = Cast<AMyAIControllerTestP>(refCharSpawn->GetController());
	}
	if (refController)
	{
		refController->GetBlackboardComp()->SetValueAsObject("BasePosition", SpawnerIA);
	}
	AddEnemy(refCharSpawn);
}

void AProjet2GameMode::AddEnemy(AAICharacterTestP* Enemy)
{
	AliveEnemies.Add(Enemy);
}

void AProjet2GameMode::RemoveEnemy(AAICharacterTestP* Enemy)
{
	AliveEnemies.Remove(Enemy);
}

void AProjet2GameMode::AddTargetPoint(ABotTargetPointTestP* TargetPoint)
{
	UE_LOG(LogTemp, Warning, TEXT("Add TP"));
	TargetPoints.Add(TargetPoint);

	if(TargetPoints.Num() == 9)
	{
		UE_LOG(LogTemp, Warning, TEXT("TP PLUS 10"));
		int RandomInt = FMath::RandRange(0, TargetPoints.Num()-1);
		TargetPoints[RandomInt]->SpawnFruitOnPoint();
	}
}
