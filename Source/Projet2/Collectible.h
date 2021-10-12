// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Collectible.generated.h"

UCLASS()
class PROJET2_API ACollectible : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectible();

	//Reference to this object
	ACollectible* AThisObject = nullptr;

	UStaticMeshComponent* StaticMesh;
	
	bool bIsCarried = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact() override;

	virtual void Pickup();
	virtual void Drop();
};
