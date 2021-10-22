// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDestroyAI.h"
#include "MyAIController.h"
#include "AICharacter.h"
#include "Projet2GameMode.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTDestroyAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){

    AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	AAICharacter* IAchara = Cast<AAICharacter>(AICon->GetCharacter());
	
	if (IAchara != nullptr)
	{
		if (AICon->GetBlackboardComp()->GetValueAsBool("GoBackToBase") == true)
		{			
			AProjet2GameMode* GameMode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
			GameMode->RemoveEnemy(IAchara);
			IAchara->Destroy();
			GameMode->NumberOfEnnemySpawn--;
			GameMode->MakeCheckForSpawn();
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
