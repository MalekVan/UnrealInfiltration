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
		ASecondActor = World->SpawnActor<AActor>(ASecondActorClass, FVector(0.f,1000.f,200.f), FRotator(0.0f,0.0f,0.0f), SpwnParams);
	}
	OtherMeshComponent = Cast<UStaticMeshComponent>(ASecondActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	OtherMeshComponent->OnComponentHit.AddUniqueDynamic(this, &AMyActorTest::OnHit);
	
	MeshComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyActorTest::OnStaticMeshBeginOverlap);
	MeshComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AMyActorTest::StaticMeshBoxOnOverlapEnd);

	StartPosition = ASecondActor->GetActorLocation();
	EndPosition = StartPosition + FVector(500,0,0);
	
	DirectionEndPosition = (EndPosition - StartPosition);
	DirectionEndPosition.Normalize();
	
	DirectionStartPosition = (StartPosition - EndPosition);
	DirectionStartPosition.Normalize();
}

// Called every frame
void AMyActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(ASecondActor)
	{
		if(bCanMove)
		{
			FVector Direction = ASecondActor->GetActorLocation() + ASecondActor->GetActorForwardVector();
			if(Direction.Equals(ASecondActor->GetActorLocation() + DirectionEndPosition)) // Si on se dirige vers la position de fin
			{
				if(ASecondActor->GetActorLocation().X >= EndPosition.X)
				{
					ASecondActor->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
				} else
				{
					ASecondActor->SetActorLocation(FVector(Direction.X + Direction.X * DeltaTime, Direction.Y, Direction.Z));
				}
			} else if(Direction.Equals(ASecondActor->GetActorLocation() + DirectionStartPosition)) // Si on se dirige vers la position de départ
				{
				if(ASecondActor->GetActorLocation().X <= StartPosition.X)
				{
					ASecondActor->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
				} else
				{
					ASecondActor->SetActorLocation(FVector( Direction.X - Direction.X * DeltaTime, Direction.Y, Direction.Z));
				}
			}
		}		
	}
}

void AMyActorTest::OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//ASecondActor->SetActorHiddenInGame(false);
}

void AMyActorTest::StaticMeshBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ASecondActor->SetActorHiddenInGame(true);
}

void AMyActorTest::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	bCanMove = false;
}
