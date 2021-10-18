// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "SpawnerOfIA.h"
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

	UFUNCTION()
	void OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

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

	bool bCanMove;
	bool bIsDetecting;
	bool bHaveFruitInHand;
	bool bFruitToDropDown;
	bool bGoBackToZone;
};
