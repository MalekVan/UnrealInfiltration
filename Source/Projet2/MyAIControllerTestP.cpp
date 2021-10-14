// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIControllerTestP.h"
#include "BotTargetPointTestP.h"
#include "AICharacterTestP.h"
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
}


void AMyAIControllerTestP::OnPossess(APawn* InPawn)
{
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
	}
}

