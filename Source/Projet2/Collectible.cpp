// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectible.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projet2Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AThisObject = this;
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UStaticMeshComponent*> StaticComps = TArray<UStaticMeshComponent*>();
	GetComponents<UStaticMeshComponent>(StaticComps);
	StaticMesh = *StaticComps.GetData();
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectible::Interact()
{
	Pickup();
}

void ACollectible::Pickup()
{	
	UE_LOG(LogClass, Log, TEXT("Pickup %s"), *GetName());
	if(!bIsCarried)
	{
		bIsCarried = true;
		SetActorEnableCollision(false);
		TArray<USkeletalMeshComponent*> PlayerMeshComponents = TArray<USkeletalMeshComponent*>();
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		FName socket = TEXT("SocketNourriture");

		USkeletalMeshComponent* mesh = player->GetMesh();

		const USkeletalMeshSocket* socketInstance = mesh->GetSocketByName(socket);
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		
		this->AttachToComponent(mesh, rules, socketInstance->GetFName());
		SetActorRelativeLocation(FVector(0.0,40,100));
	}
}

void ACollectible::Drop()
{
	bIsCarried = false;
	UE_LOG(LogClass, Log, TEXT("Drop %s"), *GetName());
	SetActorRelativeLocation(FVector(0.0,40.0,0.0));
	this->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	SetActorEnableCollision(true);
}
