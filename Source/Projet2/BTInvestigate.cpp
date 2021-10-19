// Fill out your copyright notice in the Description page of Project Settings.


#include "BTInvestigate.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTInvestigate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BbComp = OwnerComp.GetBlackboardComponent();
	FHitResult hitResult;
	FVector start = OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation();
	//start.Z += 100;
	FVector forward = BbComp->GetValueAsVector("LastPlayerDirection");

	FVector end = start + (forward * 1000000); 

	FCollisionQueryParams TraceParam;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, TraceParam);

	if (bHit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("JoueurPos", hitResult.Location);
		UE_LOG(LogTemp, Warning, TEXT("RAYCAST"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Investigate"));


	return EBTNodeResult::Succeeded;
}