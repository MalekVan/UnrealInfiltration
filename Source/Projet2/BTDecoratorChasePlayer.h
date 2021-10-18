// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecoratorChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API UBTDecoratorChasePlayer : public UBTDecorator
{
	GENERATED_BODY()
	
public :
	UBTDecoratorChasePlayer();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPlayerNextToMe;
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
