// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
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
	
	void ClimbLadder(ACharacter* Player);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	FVector LowerPosition;
	UPROPERTY(EditAnywhere)
	FVector HigherPosition;
};
