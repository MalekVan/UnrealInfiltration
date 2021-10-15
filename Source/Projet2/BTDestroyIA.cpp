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
			IAchara->Destroy();
			AProjet2GameMode* Gamemode = Cast<AProjet2GameMode>(GetWorld()->GetAuthGameMode());
			Gamemode->NumberOfEnnemySpawn--;
			Gamemode->MakeCheckForSpawn();
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
