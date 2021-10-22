// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceDataControl.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTServiceDataControl::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BBComponent = OwnerComp.GetBlackboardComponent();
	if (BBComponent->GetValueAsBool("DetectPlayer"))
	{
		APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (Player->GetActorLocation() != BBComponent->GetValueAsVector("PlayerPos"))
		{
			BBComponent->SetValueAsVector("PlayerPos", Player->GetActorLocation());
			BBComponent->SetValueAsVector("LastPlayerDirection", Player->GetActorForwardVector());
		}
	}
}
