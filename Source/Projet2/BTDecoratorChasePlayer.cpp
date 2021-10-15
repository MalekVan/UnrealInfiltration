// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecoratorChasePlayer.h"
#include "MyAIControllerTestP.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecoratorChasePlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AMyAIControllerTestP* controller = Cast<AMyAIControllerTestP>(OwnerComp.GetOwner());
	if (playerNextToMe)
	{
		UE_LOG(LogTemp, Warning, TEXT("DECORATOR CHASE PLAYER ACTIVE"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DECORATOR CHASE PLAYER NOT ACTIVE"));
	}
	
	return controller->GetBlackboardComponent()->GetValueAsBool("DetectPlayer") == playerNextToMe;
}
