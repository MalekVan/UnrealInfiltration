// Fill out your copyright notice in the Description page of Project Settings.


#include "BTChasePlayer.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	AMyAIController* Controller = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	FVector PlayerLocation = BBComp->GetValueAsVector("PlayerPos");
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("WasChasing", true);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
