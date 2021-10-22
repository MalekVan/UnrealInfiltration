// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTargetPointSelection.h"

#include "AICharacter.h"
#include "BotTargetPoint.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
 
	/*If the Controller is valid:
	1)Get the Blackboard Component and the Current Point of the bot
	2)Search for the next point, which will be different from the Current Point*/
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

		if (AICon->ListOfDestinationPoints.Num() > 0)
		{
			ABotTargetPoint* NextTargetPoint = AICon->ListOfDestinationPoints[0];
			BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
			return EBTNodeResult::Succeeded;

		}
		else
		{
			BlackboardComp->SetValueAsBool("GoBackToBase", true);
			Cast<AAICharacter>(AICon->GetCharacter())->bGoBackToZone = true;
			return EBTNodeResult::Failed;

		}
		
	}
	return EBTNodeResult::Failed;
	
}