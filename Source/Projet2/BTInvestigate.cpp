// Fill out your copyright notice in the Description page of Project Settings.


#include "BTInvestigate.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTInvestigate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	FHitResult HitResult;
	FVector Start = OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation();
	//start.Z += 100;
	FVector Forward = BBComp->GetValueAsVector("LastPlayerDirection");

	FVector End = Start + (Forward * 1000000); 

	FCollisionQueryParams TraceParam;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParam);

	if (bHit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("PlayerPos", HitResult.Location);
	}
	return EBTNodeResult::Succeeded;
}