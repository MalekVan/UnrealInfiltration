// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTargetPointSelectionTestP.h"
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
		ABotTargetPointTestP* CurrentPoint = Cast<ABotTargetPointTestP>(BlackboardComp->GetValueAsObject("LocationToGo"));
 
		TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();
       
		//This variable will contain a random index in order to determine the next possible point
		int32 RandomIndex;
 
		//Here, we store the possible next target point
		ABotTargetPointTestP* NextTargetPoint = nullptr;
 
		//Find a next point which is different from the current one
		do
		{
			RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num()-1);
			//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
			NextTargetPoint = Cast<ABotTargetPointTestP>(AvailableTargetPoints[RandomIndex]);
		} while (CurrentPoint == NextTargetPoint);
 
		//Update the next location in the Blackboard so the bot can move to the next Blackboard value
		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
 
		//TASK est un succes
		return EBTNodeResult::Succeeded;
	}
	//TASK est un échec
	return EBTNodeResult::Failed;
}