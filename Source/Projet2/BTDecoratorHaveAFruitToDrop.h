// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecoratorHaveAFruitToDrop.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API UBTDecoratorHaveAFruitToDrop : public UBTDecorator
{
	UPROPERTY(EditAnywhere)
	bool bFruitToDropDown;
	
	GENERATED_BODY()
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
