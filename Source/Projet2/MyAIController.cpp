// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "BotTargetPoint.h"
#include "AICharacter.h"
#include "Projet2GameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"


AMyAIController::AMyAIController() //Constructor
{
	// Already a blackboard and a behaviour tree in AAIController so no need to recreate them ? 
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	
	LocationToGoKey = "LocationToGo";
	DetectPlayerKey = "DetectPlayer";
	
	ListOfDestinationPoints = TArray<ABotTargetPoint*>();
}


void AMyAIController::OnPossess(APawn* InPawn)
{
	SetGenericTeamId(0); // To differentiate AIs and player
	
	Super::OnPossess(InPawn);
 
	//Get the possessed Character and check if it's my own AI Character
	AAICharacter* AIChar = Cast<AAICharacter>(InPawn);

	// If our character exists then we can get the reference to his blackboard and his behaviour tree 
	if (AIChar)
	{
		if (AIChar->BehaviorTree->BlackboardAsset) // Get reference to blackboard
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}
		if (AIChar->BehaviorTree) //Get reference to behaviour tree
		{
			BehaviorComp->StartTree(*AIChar->BehaviorTree);
		}

		// Fill array with all available target points
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), BotTargetPoints);

		AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
		if(Gamemode->NumberOfFruitsSpawn < Gamemode->NumberOfFruitsMax)
		{
			AIChar->bHaveFruitInHand = true;
			// Spawn fruit in corresponding socket
			AIChar->AttachAFruitToSocket(AIChar->CreateFruit());
			if (BlackboardComp)
			{
				BlackboardComp->SetValueAsBool("FruitsToDropDown", true);
				BlackboardComp->SetValueAsBool("HaveFruitInHands", true);
				BlackboardComp->SetValueAsObject("FruitPosition", AIChar->Fruit);
			}
			ABotTargetPoint* TempEmptyPoint = GetRandomPointEmpty();
			if (TempEmptyPoint)
			{
				ListOfDestinationPoints.Add(TempEmptyPoint);
				TempEmptyPoint->bFruitOnThisTargetPoint =true;
			}

		}
		else
		{
			AIChar->bHaveFruitInHand = false;
			ListOfDestinationPoints.Add(GetRandomPoint());
			ListOfDestinationPoints.Add(GetRandomPoint());
			
		}
	}
}

ABotTargetPoint* AMyAIController::GetRandomPointEmpty()
{

	TArray<ABotTargetPoint*> ListFreeTemp;
	for (int i = 0; i < BotTargetPoints.Num(); i++)
	{
		ABotTargetPoint* tempPoint = Cast<ABotTargetPoint>(BotTargetPoints[i]);
		if (!tempPoint->bFruitOnThisTargetPoint)
		{
			ListFreeTemp.Add(tempPoint);
		}
	}
	
	int RandomIndex = FMath::RandRange(0, ListFreeTemp.Num()-1);
	
	if (ListFreeTemp.Num() <= 0 )
	{
		return nullptr;
	}
	
	return ListFreeTemp[RandomIndex];
	
}

ABotTargetPoint* AMyAIController::GetRandomPoint()
{
	int RandomIndex = FMath::RandRange(0, BotTargetPoints.Num()-1);
	return Cast<ABotTargetPoint>(BotTargetPoints[RandomIndex]);
}

