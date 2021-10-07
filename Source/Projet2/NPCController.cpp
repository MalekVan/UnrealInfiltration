// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ANPCController::ANPCController(FObjectInitializer const& objectInitializer) {
	BehaviorTreeComponent = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));
	BTree = objectInitializer.CreateDefaultSubobject<UBehaviorTree>(this, TEXT("BehaviorTree"));
	if (BehaviorTreeComponent) {
		bBoard = BehaviorTreeComponent->GetBlackboardComponent();
	}
}
void ANPCController::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BTree);
	BehaviorTreeComponent->StartTree(*BTree);
}
void ANPCController::OnPossess(APawn* const pawn) {
	Super::OnPossess(pawn);
	if (bBoard) {
		bBoard->InitializeBlackboard(*BTree->BlackboardAsset);
	}
}
UBlackboardComponent* ANPCController::GetBlackboard() const{
	return Blackboard;
}
