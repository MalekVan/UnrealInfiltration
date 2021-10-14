// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_StopChasePlayer_TestP.h"
#include "MyAIControllerTestP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBT_StopChasePlayer_TestP::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory){

	AMyAIControllerTestP* AICon = Cast<AMyAIControllerTestP>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		AICon->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200;
		return EBTNodeResult::Succeeded;
	}
	
	//TASK est un échec
	return EBTNodeResult::Failed;
}