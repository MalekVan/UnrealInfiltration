// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projet2Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Collectible.h"
#include "Projet2GameMode.h"
#include "GameHUD.h"
#include "Interactable.h"
#include "Chest.h"

//////////////////////////////////////////////////////////////////////////
// AProjet2Character

AProjet2Character::AProjet2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	//StimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliForIA"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjet2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AProjet2Character::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjet2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjet2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjet2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjet2Character::LookUpAtRate);

	InputComponent->BindAction("Run", IE_Released, this,   &AProjet2Character::RunButtonReleased);
	InputComponent->BindAction("Run", IE_Pressed, this,   &AProjet2Character::RunButtonPressed);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this,   &AProjet2Character::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this,   &AProjet2Character::ZoomOut);
}

void AProjet2Character::BeginPlay() {
	Super::BeginPlay();
	
	// Get reference to player mesh
	ComponentSkeletalMesh = GetMesh();
	
	if (ComponentSkeletalMesh)
	{
		// Get reference to player anim instance
		AnimInstanceOfSkeletalMesh = dynamic_cast<UAnimClassForPlayer*>((ComponentSkeletalMesh)? ComponentSkeletalMesh->GetAnimInstance() : nullptr);
	}

	// Get reference to camera boom
	ComponentCameraBoom = FindComponentByClass<USpringArmComponent>();
	if(ComponentCameraBoom)
	{		
		// Setup camera arm value
		fFuturValueOfZoom = ComponentCameraBoom->TargetArmLength;
	}
	
	GameMode = Cast<AProjet2GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AProjet2Character::UpdateMovementState()
{
	if (bIsCarry)
	{
		if (GetCharacterMovement()->Velocity.Size() > 300)
		{
			GetCharacterMovement()->MaxWalkSpeed = 300;
		}
	}
}

void AProjet2Character::RunButtonReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

void AProjet2Character::RunButtonPressed()
{
	if (!bIsCarry) // If the player is holding something he cannot run 
	{
		GetCharacterMovement()->MaxWalkSpeed = 500;
	}
}

void AProjet2Character::ZoomIn()
{
	if (ComponentCameraBoom->TargetArmLength > iMinCameraZoom)
	{
		fFuturValueOfZoom = ComponentCameraBoom->TargetArmLength - iStepOfWheeling;
	}
}

void AProjet2Character::ZoomOut()
{
	if (ComponentCameraBoom->TargetArmLength < iMaxCameraZoom)
	{
		fFuturValueOfZoom = ComponentCameraBoom->TargetArmLength + iStepOfWheeling;
	}
}

void AProjet2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ComponentCameraBoom->TargetArmLength != fFuturValueOfZoom)
	{
		if (fFuturValueOfZoom > ComponentCameraBoom->TargetArmLength)
		{
			ComponentCameraBoom->TargetArmLength += iSpeedOfWheeling;
			if (fFuturValueOfZoom <ComponentCameraBoom->TargetArmLength){fFuturValueOfZoom = ComponentCameraBoom->TargetArmLength;}
		}
		if (fFuturValueOfZoom < ComponentCameraBoom->TargetArmLength)
		{
			ComponentCameraBoom->TargetArmLength -= iSpeedOfWheeling;
			if (fFuturValueOfZoom >ComponentCameraBoom->TargetArmLength){fFuturValueOfZoom = ComponentCameraBoom->TargetArmLength;}
		}
	}
}

void AProjet2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjet2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProjet2Character::MoveForward(float Value)
{
	if(bCanMove)
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AProjet2Character::MoveRight(float Value)
{
	if(bCanMove)
	{
		if ( (Controller != nullptr) && (Value != 0.0f) )
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
		
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void AProjet2Character::Interact()
{
	if(AnimInstanceOfSkeletalMesh->bIsSitting)
	{
		LevelChair->Interact(this);
		return;
	}
	// Detection of all AInteractable around the player
	TArray<AActor*> OverlappingActors = TArray<AActor*>();
	GetOverlappingActors(OverlappingActors, AInteractable::StaticClass());
	
	if(!bIsCarry)
	{	
		if(OverlappingActors.Num() == 1) // If there's only one, interact with it
		{
			AActor* OverlappedActor = *OverlappingActors.GetData();
			if(AInteractable* InteractableActor = Cast<AInteractable>(OverlappedActor))
			{
				if(OverlappedActor->IsA(ACollectible::StaticClass()))
				{
					HoldedCollectible = Cast<ACollectible>(OverlappedActor);
					bIsCarry = true;
				}
				InteractableActor->Interact(this);
			}
		}
		else if(OverlappingActors.Num() > 1) // If there are many, interact with the closest one
		{
			float ClosestDistance = 9001;
			AActor* ClosestActor = nullptr;
			for (AActor* Actor : OverlappingActors)
			{
				float Distance = GetDistanceBetweenVectors(this->GetActorLocation(), Actor->GetActorLocation());
				if(Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					ClosestActor = Actor;
				}
			}
			if(AInteractable* InteractableActor = Cast<AInteractable>(ClosestActor))
			{
				if(ClosestActor->IsA(ACollectible::StaticClass()))
				{
					HoldedCollectible = Cast<ACollectible>(ClosestActor);
					bIsCarry = true;
				}				
				InteractableActor->Interact(this);
			}
		}
		AnimInstanceOfSkeletalMesh->bIsCarry = bIsCarry;
	} else
	{
		if(OverlappingActors.Num() == 1) // If there's only one, interact with it
		{
			if(AChest* Chest = Cast<AChest>(*OverlappingActors.GetData()))
			{
				Chest->Interact(this);
			}
		}
		else if(OverlappingActors.Num() > 1) // If there are many, interact with the closest one
		{
			for(AActor* Actor : OverlappingActors)
			{
				if(AChest* Chest = Cast<AChest>(*OverlappingActors.GetData()))
				{
					Chest->Interact(this);
					break;
				}
			}
		} else
		{
			HoldedCollectible->Drop();
			HoldedCollectible = nullptr;
			bIsCarry = false;
			AnimInstanceOfSkeletalMesh->bIsCarry = bIsCarry;
		}
	}
	UpdateMovementState();
}

float AProjet2Character::GetDistanceBetweenVectors(FVector From, FVector To)
{
	return (sqrt(pow(To.X - From.X, 2) + pow(To.Y - From.Y, 2) + pow(To.Z - From.Z, 2)));
}