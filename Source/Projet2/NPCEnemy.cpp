// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCEnemy.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
// Sets default values
ANPCEnemy::ANPCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCEnemy::BeginPlay()
{
	Super::BeginPlay();

	//set material Color for the character
	UMaterialInstanceDynamic* const materialInstance = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	if (materialInstance)
	{
		materialInstance->SetVectorParameterValue("BodyColor", FLinearColor(1.f, 0.f, 1.f));
		GetMesh()->SetMaterial(0, materialInstance);
	}
}

// Called every frame
void ANPCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

