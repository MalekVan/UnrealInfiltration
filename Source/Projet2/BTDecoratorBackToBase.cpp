// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecoratorBackToBase.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecoratorBackToBase::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool("GoBackToBase") == bGoBackToBase;
}
