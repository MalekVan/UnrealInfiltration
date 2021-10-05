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
	FActorSpawnParameters SpwnParams;
	if(World)
	{
		ASecondActor = World->SpawnActor<AActor>(ASecondActorClass, this->GetActorLocation() + FVector(50.f,0.f,0.f), FRotator(0.0f,0.0f,0.0f), SpwnParams);
	}
	
	MeshComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyActorTest::OnStaticMeshBeginOverlap);
	MeshComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AMyActorTest::StaticMeshBoxOnOverlapEnd);
}

// Called every frame
void AMyActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ASecondActor->SetActorRelativeLocation(ASecondActor->GetActorLocation() + FVector(1,0,0) * MovementSpeed *  DeltaTime);
}

void AMyActorTest::OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//ASecondActor->SetActorHiddenInGame(false);
}

void AMyActorTest::StaticMeshBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ASecondActor->SetActorHiddenInGame(true);
}
