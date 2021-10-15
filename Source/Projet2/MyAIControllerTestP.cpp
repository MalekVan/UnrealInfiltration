// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIControllerTestP.h"
#include "BotTargetPointTestP.h"
#include "AICharacterTestP.h"
#include "Projet2GameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"


AMyAIControllerTestP::AMyAIControllerTestP() //Constructeur
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

 
	LocationToGoKey = "LocationToGo";
	DetectPlayerKey = "DetectPlayer";
	
	ListOfDestinationPoints = TArray<ABotTargetPointTestP*>();
}


void AMyAIControllerTestP::OnPossess(APawn* InPawn)
{
	SetGenericTeamId(0); // pour differencier IA et joris
	
	Super::OnPossess(InPawn);
 
	//Get the possessed Character and check if it's my own AI Character
	AAICharacterTestP* AIChar = Cast<AAICharacterTestP>(InPawn);

	//Si notre character existe alors on peut avoir une référence vers son blackboard + son BehaviourTree. 
	if (AIChar)
	{
		if (AIChar->BehaviorTree->BlackboardAsset) //Avoir la référence vers notre Blackboard.
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}
		if (AIChar->BehaviorTree) //Avoir la référence vers notre BehaviourTree
		{
			BehaviorComp->StartTree(*AIChar->BehaviorTree);
		}

		//Remplir le tableau avec tout les targets points dispos.
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPointTestP::StaticClass(), BotTargetPoints);

		AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
		if(Gamemode->NumberOfFruitsSpawn < Gamemode->NumberOfFruitsMax)
		{
			AIChar->HaveFruitInHand = true;
			//faire spawn le fruit dans le socket correspondant.
			AIChar->AttachAFruitToSocket(AIChar->CreateFruit());
			if (BlackboardComp)
			{
				BlackboardComp->SetValueAsBool("FruitsToDropDown", true);
				BlackboardComp->SetValueAsBool("HaveFruitInHands", true);
				BlackboardComp->SetValueAsObject("FruitPosition", AIChar->Fruit);
			}
			ABotTargetPointTestP* TempEmptyPoint = GetRandomPointEmpty();
			if (TempEmptyPoint)
			{
				ListOfDestinationPoints.Add(TempEmptyPoint);
			}

		}
		else
		{
			AIChar->HaveFruitInHand = false;
			ListOfDestinationPoints.Add(GetRandomPoint());
			ListOfDestinationPoints.Add(GetRandomPoint());
			
		}
	}
}

ABotTargetPointTestP* AMyAIControllerTestP::GetRandomPointEmpty()
{

	TArray<ABotTargetPointTestP*> ListFreeTemp;
	for (int i = 0; i < BotTargetPoints.Num(); i++)
	{
		ABotTargetPointTestP* tempPoint = Cast<ABotTargetPointTestP>(BotTargetPoints[i]);
		if (!tempPoint->FruitOnThisTargetPoint)
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

ABotTargetPointTestP* AMyAIControllerTestP::GetRandomPoint()
{
	int RandomIndex = FMath::RandRange(0, BotTargetPoints.Num()-1);
	return Cast<ABotTargetPointTestP>(BotTargetPoints[RandomIndex]);
}

