// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectible.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projet2Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UStaticMeshComponent*> StaticComps = TArray<UStaticMeshComponent*>();
	GetComponents<UStaticMeshComponent>(StaticComps);
	if (StaticComps.Num() > 0)
	{
		StaticMesh = StaticComps[0];
	}
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectible::Interact(ACharacter* Player)
{
	Pickup(Player);
}

void ACollectible::Pickup(ACharacter* Player)
{
	if(!bIsCarried)
	{
		bIsCarried = true;
		SetActorEnableCollision(false);
		StaticMesh->SetSimulatePhysics(false);

		FName Socket = TEXT("FoodSocket");

		USkeletalMeshComponent* Mesh = Player->GetMesh();

		const USkeletalMeshSocket* SocketInstance = Mesh->GetSocketByName(Socket);
		FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		
		this->AttachToComponent(Mesh, AttachmentRules, SocketInstance->GetFName());
		SetActorRelativeLocation(FVector(0.0,40,100));
		OwnerOfTheObject = Player;
	}
}

void ACollectible::Drop()
{
	if(AProjet2Character* Player = Cast<AProjet2Character>(OwnerOfTheObject))
		Player->GetCharacterMovement()->MaxWalkSpeed = 500;
	
	SetActorRelativeLocation(FVector(0.0,40.0,0.0));
	this->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	SetActorEnableCollision(true);
	StaticMesh->SetSimulatePhysics(false);
	bIsCarried = false;
}
