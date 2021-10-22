// Fill out your copyright notice in the Description page of Project Settings.

#include "BTStopChasePlayer.h"
#include "MyAIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTStopChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){

	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		AICon->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("WasChasing", false);

		AAICharacter* AIChar = Cast<AAICharacter>(AICon->GetCharacter());
		if (AIChar && AIChar->Fruit)
		{
			if (AIChar->Fruit->bIsCarried && !(AIChar->Fruit->OwnerOfTheObject == AIChar))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("GoBackToBase", true);
			}
		}
		return EBTNodeResult::Succeeded;
		
	}	
	//Task failed
	return EBTNodeResult::Failed;
}