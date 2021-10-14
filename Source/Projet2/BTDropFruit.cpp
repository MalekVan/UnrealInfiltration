// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDropFruit.h"
#include "MyAIControllerTestP.h"
#include "AICharacterTestP.h"
#include "BotTargetPointTestP.h"

EBTNodeResult::Type UBTDropFruit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());
	AAICharacterTestP* IAchara = Cast<AAICharacterTestP>(AICon)
	if (AICon && IAchara)
	{
		if (IAchara->HaveFruit)
		{
			UE_LOG(LogTemp, Warning, TEXT("OVERLAP IA"));

			ABotTargetPointTestP* tempPoint = AICon->ListOfDestinationPoints[0];
			ACollectible* fruit =  IAchara->Fruit;
			
			if (fruit && tempPoint)
			{
				IAchara->PutDownAFruit();
				fruit->StaticMesh->SetupAttachment(tempPoint->GetRootComponent());
				fruit->StaticMesh->SetSimulatePhysics(false);
				tempPoint->FruitOnThisTargetPoint=true;
				return  EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}

