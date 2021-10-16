// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDestroyIA.h"
#include "MyAIControllerTestP.h"
#include "AICharacterTestP.h"
#include "Projet2GameMode.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTDestroyIA::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){

    AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());
	AAICharacterTestP* IAchara = Cast<AAICharacterTestP>(AICon->GetCharacter());
	
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
