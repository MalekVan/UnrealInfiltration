// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceDataControl.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API UBTServiceDataControl : public UBTService
{
	GENERATED_BODY()
	protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
