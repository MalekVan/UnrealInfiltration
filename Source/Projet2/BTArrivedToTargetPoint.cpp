// Fill out your copyright notice in the Description page of Project Settings.


#include "BTArrivedToTargetPoint.h"
#include "MyAIControllerTestP.h"

EBTNodeResult::Type UBTArrivedToTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());

	if (AICon && AICon->ListOfDestinationPoints.Num() > 0)
	{
		AICon->ListOfDestinationPoints.RemoveAt(0);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
}
