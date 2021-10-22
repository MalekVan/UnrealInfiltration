// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTakeBackMyFruit.h"
#include "MyAIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTakeBackMyFruit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	AAICharacter* IAchara = Cast<AAICharacter>(AICon->GetCharacter());
	
	if (AICon && AICon->ListOfDestinationPoints.Num() > 0)
	{
		//Attach fruit to AI again
		//Set HaveFruitInHand to true
		
		IAchara->AttachAFruitToSocket(IAchara->Fruit);
		IAchara->bHaveFruitInHand = true;
		AICon->GetBlackboardComp()->SetValueAsBool("HaveFruitInHands", true);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
