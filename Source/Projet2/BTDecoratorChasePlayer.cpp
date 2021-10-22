// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecoratorChasePlayer.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecoratorChasePlayer::UBTDecoratorChasePlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructeur du Decorator"));
	FlowAbortMode = EBTFlowAbortMode::Both;  
}

bool UBTDecoratorChasePlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	AMyAIController* Controller = Cast<AMyAIController>(OwnerComp.GetOwner());

	if (Controller->GetBlackboardComp() == OwnerComp.GetBlackboardComponent())
	{
		
	}	
	return Controller->GetBlackboardComponent()->GetValueAsBool("DetectPlayer") == bPlayerNextToMe;
}

