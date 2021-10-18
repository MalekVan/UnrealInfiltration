// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecoratorHaveAFruitToDrop.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecoratorHaveAFruitToDrop::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool("FruitsToDropDown") == bFruitToDropDown;
}
