// Fill out your copyright notice in the Description page of Project Settings.


#include "BTArrivedToTargetPoint.h"
#include "MyAIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTArrivedToTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	AAICharacter* IAchara = Cast<AAICharacter>(AICon->GetCharacter());

	if (AICon && AICon->ListOfDestinationPoints.Num() > 0)
	{
		AICon->ListOfDestinationPoints.RemoveAt(0);

		if (AICon->ListOfDestinationPoints.Num() <= 0) //J'ai atteint la destination finale de mon tableau de destination.
		{
			//Si j'atteint ma destination et que je devais poser un fruit, alors je n'ai plus besoin d'en poser.
			AICon->GetBlackboardComp()->SetValueAsBool("FruitsToDropDown", false);
			AICon->GetBlackboardComp()->SetValueAsBool("GoBackToBase", true);
		}
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
}
