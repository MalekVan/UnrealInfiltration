// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTest.h"

// Sets default values
AMyActorTest::AMyActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("RootScene"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	MeshComponent->SetupAttachment(RootComponent);	
}

// Called when the game starts or when spawned
void AMyActorTest::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if(World)
	{
		ASecondActor = World->SpawnActor<AOtherActor>(AOtherActor::StaticClass());		
		ASecondActor->SetActorHiddenInGame(true);
	}
	
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyActorTest::OnStaticMeshBeginOverlap);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &AMyActorTest::StaticMeshBoxOnOverlapEnd);
}

// Called every frame
void AMyActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActorTest::OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ASecondActor->SetActorHiddenInGame(false);
}

void AMyActorTest::StaticMeshBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASecondActor->SetActorHiddenInGame(true);
}
