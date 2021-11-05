// Fill out your copyright notice in the Description page of Project Settings.


#include "BTChasePlayer.h"
#include "MyAIController.h"
#include "AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

EBTNodeResult::Type UBTChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	AMyAIController* Controller = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	
	if (AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner()))
	{
		AICon->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 400;
	}

	//Ajout paul :
	Controller->LaunchFollowPlayerTimer();
	
	FVector PlayerLocation = BBComp->GetValueAsVector("PlayerPos");
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("WasChasing", true);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
