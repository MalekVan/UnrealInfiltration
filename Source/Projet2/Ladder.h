// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Projet2Character.h"
#include "Ladder.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API ALadder : public AInteractable
{
	GENERATED_BODY()
	
public:
	ALadder();

	void Interact(ACharacter* Player) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	FVector LowerPosition;
	UPROPERTY(EditAnywhere)
	FVector HigherPosition;
	
private:	
	void ClimbLadder(AProjet2Character* Player);
};
