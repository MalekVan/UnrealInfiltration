// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecoratorBackToBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API UBTDecoratorBackToBase : public UBTDecorator
{
	GENERATED_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GoBackToBase;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
