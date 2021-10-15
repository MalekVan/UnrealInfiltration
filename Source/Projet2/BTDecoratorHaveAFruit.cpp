// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecoratorHaveAFruit.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecoratorHaveAFruit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool("HaveFruitInHands") == HaveAFruit;
}