// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Chest.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API AChest : public AInteractable
{
	GENERATED_BODY()

	public:
	
	void Interact(ACharacter* Player) override;

	protected:

	void StoreFruit(ACharacter* Player);
};
