// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecoratorChasePlayer.h"
#include "MyAIControllerTestP.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecoratorChasePlayer::UBTDecoratorChasePlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructeur du Decorator"));
	FlowAbortMode = EBTFlowAbortMode::Both;  
}

bool UBTDecoratorChasePlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	AMyAIControllerTestP* controller = Cast<AMyAIControllerTestP>(OwnerComp.GetOwner());

	if (controller->GetBlackboardComp() == OwnerComp.GetBlackboardComponent())
	{
		
	}
	UE_LOG(LogTemp, Warning, TEXT("DECORATOR RRRRRR"));

	
	return controller->GetBlackboardComponent()->GetValueAsBool("DetectPlayer") == bPlayerNextToMe;
}

