// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Chair.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API AChair : public AInteractable
{
	GENERATED_BODY()
	
public:

	AChair();

	void Interact(ACharacter* Player) override;
	
	void SitOnChair(ACharacter* Player);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	FVector SittingPosition;
};
