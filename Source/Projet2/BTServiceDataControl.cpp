// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceDataControl.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTServiceDataControl::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BbComponent = OwnerComp.GetBlackboardComponent();
	if (BbComponent->GetValueAsBool("DetectPlayer"))
	{
		APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (player->GetActorLocation() != BbComponent->GetValueAsVector("JoueurPos"))
		{
			BbComponent->SetValueAsVector("JoueurPos", player->GetActorLocation());
			BbComponent->SetValueAsVector("LastPlayerDirection", player->GetActorForwardVector());
		}
	}
}
