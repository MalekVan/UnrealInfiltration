// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDropFruit.h"
#include "MyAIControllerTestP.h"
#include "AICharacterTestP.h"
#include "BotTargetPointTestP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AnimClassForIA.h"

EBTNodeResult::Type UBTDropFruit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());
	AAICharacterTestP* IAchara = Cast<AAICharacterTestP>(AICon->GetCharacter());
	UAnimClassForIA* animClass = Cast<UAnimClassForIA>(IAchara->GetMesh()->GetAnimInstance());
	
	if (AICon && IAchara && AICon->GetBlackboardComp()->GetValueAsBool("HaveFruitInHands"))
	{
		if (IAchara->bHaveFruitInHand)
		{
			UE_LOG(LogTemp, Warning, TEXT("OVERLAP IA"));

			ABotTargetPointTestP* tempPoint = AICon->ListOfDestinationPoints[0];
			ACollectible* fruit =  IAchara->Fruit;
			
			if (fruit && tempPoint)
			{
				if(!AICon->GetBlackboardComp()->GetValueAsBool("DetectPlayer"))
				{
					IAchara->PutDownAFruit();
					FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
					fruit->StaticMesh->AttachToComponent(tempPoint->GetRootComponent(), AttachmentTransformRules);
					fruit->SetActorRelativeLocation(FVector(0.0,0.0,-30.0));
					fruit->StaticMesh->SetSimulatePhysics(false);
					tempPoint->bFruitOnThisTargetPoint = true;

					//animClass->IsCarry = false;

					//Le joueur perd le fruit de ses mains
					IAchara->bHaveFruitInHand = false;
					AICon->GetBlackboardComp()->SetValueAsBool("HaveFruitInHands", false);
				} else
				{					
					IAchara->PutDownAFruit();
					fruit->StaticMesh->SetSimulatePhysics(false);
					IAchara->bHaveFruitInHand = false;
					AICon->GetBlackboardComp()->SetValueAsBool("HaveFruitInHands", false);
				}
			}
		}
	}
	return  EBTNodeResult::Succeeded;
}

