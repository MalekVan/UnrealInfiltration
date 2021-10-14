// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyAIControllerTestP.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API AMyAIControllerTestP : public AAIController
{
	GENERATED_BODY()

	/*Behavior tree ref*/
	UBehaviorTreeComponent* BehaviorComp;
   
	/*----------Blackboard----------*/
	UBlackboardComponent* BlackboardComp;
 
	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey = "LocationToGo";
	FName DetectPlayerKey = "DetectPlayer";
 
	/*All targets point availables in the level*/
	TArray<AActor*> BotTargetPoints;

 
	/*Posses is executed when the character we want to control is spawned.
	Inside this function, we initialize the blackboard and start the behavior tree*/
	virtual void OnPossess(APawn* Pawn) override;

	virtual class ABotTargetPointTestP* GetRandomPointEmpty();
	virtual ABotTargetPointTestP* GetRandomPoint();

	public:
	TArray< ABotTargetPointTestP*> ListOfDestinationPoints;


	/*----------Constructor----------*/
	AMyAIControllerTestP();
	
	UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
 
	TArray<AActor*> GetAvailableTargetPoints() { return BotTargetPoints; }
	
};
