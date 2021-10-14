// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTargetPointSelectionTestP.h"

#include "AICharacterTestP.h"
#include "BotTargetPointTestP.h"
#include "MyAIControllerTestP.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTargetPointSelectionTestP::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());
 
	/*If the Controller is valid:
	1)Get the Blackboard Component and the Current Point of the bot
	2)Search for the next point, which will be different from the Current Point*/
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

		if (AICon->ListOfDestinationPoints.Num() > 0)
		{
			ABotTargetPointTestP* NextTargetPoint = AICon->ListOfDestinationPoints[0];
			BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
			return EBTNodeResult::Succeeded;

		}
		else
		{
			BlackboardComp->SetValueAsBool("GoBackToBase", true);
			Cast<AAICharacterTestP>(AICon->GetCharacter())->GoBackToZone = true;
			return EBTNodeResult::Failed;

		}
		
	}
	return EBTNodeResult::Failed;
	
}