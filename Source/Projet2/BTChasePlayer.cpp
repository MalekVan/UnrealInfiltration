// Fill out your copyright notice in the Description page of Project Settings.


#include "BTChasePlayer.h"
#include "MyAIControllerTestP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

EBTNodeResult::Type UBTChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIControllerTestP* controller = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());
	FVector playerLocation = controller->GetBlackboardComp()->GetValueAsVector("JoueurPos");
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("WasChasing", true);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, playerLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
