// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDropFruit.h"
#include "MyAIControllerTestP.h"
#include "AICharacterTestP.h"
#include "BotTargetPointTestP.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTDropFruit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());
	AAICharacterTestP* IAchara = Cast<AAICharacterTestP>(AICon->GetCharacter());
	if (AICon && IAchara && AICon->GetBlackboardComp()->GetValueAsBool("HaveFruitInHands"))
	{
		if (IAchara->HaveFruitInHand)
		{
			UE_LOG(LogTemp, Warning, TEXT("OVERLAP IA"));

			ABotTargetPointTestP* tempPoint = AICon->ListOfDestinationPoints[0];
			ACollectible* fruit =  IAchara->Fruit;
			
			if (fruit && tempPoint)
			{
				IAchara->PutDownAFruit();
				fruit->StaticMesh->SetupAttachment(tempPoint->GetRootComponent());
				fruit->StaticMesh->SetSimulatePhysics(false);
				tempPoint->FruitOnThisTargetPoint=true;

				//Le joueur perd le fruit de ses mains
				IAchara->HaveFruitInHand = false;
				AICon->GetBlackboardComp()->SetValueAsBool("HaveFruitInHands", false);
			}
		}
		
	}
	return  EBTNodeResult::Succeeded;
	return EBTNodeResult::Failed;
}

