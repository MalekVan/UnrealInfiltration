// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameFramework/Character.h"
#include "AICharacterTestP.generated.h"


UCLASS()
class PROJET2_API AAICharacterTestP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacterTestP();

	UPROPERTY(EditAnywhere,Category = "AI")
	class UBehaviorTree* BehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void AttachAFruitToSocket(ACollectible* collectible);
	ACollectible* CreateFruit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "CollectibleToSpawn")
	TSubclassOf<ACollectible> collectibleClass;
	
	void PutDownAFruit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAcesse = "true"))
	class UAIPerceptionComponent* PerceptionComponent;
	
	class ACollectible* Fruit;

	bool IsDetecting;
	bool HaveFruitInHand;
	bool FruitToDropDown;
	bool GoBackToZone;
};
