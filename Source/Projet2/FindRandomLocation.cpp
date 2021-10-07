// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"

#include "NPCController.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BBKeys.h"

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
  {
  	ANPCController* const cont = Cast<ANPCController>(ownerComp.GetAIOwner());
  	APawn* const npc = cont->GetPawn();
  
  	
  	FVector const origin = npc->GetActorLocation();
  	FNavLocation loc;
  
  	UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
  	if (navSys->GetRandomPointInNavigableRadius(origin, SearchRadius, loc, nullptr))
  	{
  		cont->GetBlackboard()->SetValueAsVector(bb_keys::targetLocation, loc.Location);
  	}
  	return EBTNodeResult::Type();
  }


