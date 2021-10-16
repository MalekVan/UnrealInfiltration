// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTakeBackMyFruit.h"
#include "MyAIControllerTestP.h"
#include "AICharacterTestP.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTakeBackMyFruit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());
	AAICharacterTestP* IAchara = Cast<AAICharacterTestP>(AICon->GetCharacter());
	
	if (AICon && AICon->ListOfDestinationPoints.Num() > 0)
	{
		//Attacher le fruit à l'IA à nouveau
		//Passer HaveFruitInHand a true
		
		IAchara->AttachAFruitToSocket(IAchara->Fruit);
		IAchara->bHaveFruitInHand = true;
		AICon->GetBlackboardComp()->SetValueAsBool("HaveFruitInHands", true);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
