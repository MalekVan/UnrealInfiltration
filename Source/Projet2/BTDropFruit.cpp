// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDropFruit.h"
#include "MyAIController.h"
#include "AICharacter.h"
#include "BotTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AnimClassForAI.h"

EBTNodeResult::Type UBTDropFruit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	AAICharacter* IAchara = Cast<AAICharacter>(AICon->GetCharacter());
	
	if (AICon && IAchara && AICon->GetBlackboardComp()->GetValueAsBool("HaveFruitInHands"))
	{
		if (IAchara->bHaveFruitInHand)
		{
			ABotTargetPoint* TempPoint = AICon->ListOfDestinationPoints[0];
			ACollectible* Collectible =  IAchara->Fruit;
			
			if (Collectible && TempPoint)
			{
				if(!AICon->GetBlackboardComp()->GetValueAsBool("DetectPlayer"))
				{
					IAchara->PutDownAFruit();
					FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
					Collectible->StaticMesh->AttachToComponent(TempPoint->GetRootComponent(), AttachmentTransformRules);
					Collectible->SetActorRelativeLocation(FVector(0.0,0.0,-30.0));
					Collectible->StaticMesh->SetSimulatePhysics(false);
					TempPoint->bFruitOnThisTargetPoint = true;

					//Player drops fruit
					IAchara->bHaveFruitInHand = false;
					AICon->GetBlackboardComp()->SetValueAsBool("HaveFruitInHands", false);
				} else
				{					
					IAchara->PutDownAFruit();
					Collectible->StaticMesh->SetSimulatePhysics(false);
					IAchara->bHaveFruitInHand = false;
					AICon->GetBlackboardComp()->SetValueAsBool("HaveFruitInHands", false);
				}
			}
		}
	}
	return  EBTNodeResult::Succeeded;
}

