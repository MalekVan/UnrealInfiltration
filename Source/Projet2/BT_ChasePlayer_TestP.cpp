// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIControllerTestP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BT_ChasePlayer_TestP.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

//Changer la vitesse de l'IA pour la rendre plus rapide. 

EBTNodeResult::Type UBT_ChasePlayer_TestP::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory){

	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		AICon->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 400;
		return EBTNodeResult::Succeeded;
	}
	
	//TASK est un échec
	return EBTNodeResult::Failed;
}