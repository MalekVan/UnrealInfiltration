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

//////////////////////////////////////////////////////////////////////////
// AProjet2Character

AProjet2Character::AProjet2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjet2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjet2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjet2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjet2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjet2Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjet2Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjet2Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjet2Character::OnResetVR);
	
	
	//PERSONNAL INPUT
	InputComponent->BindAction("TakeObject", IE_Released, this,   &AProjet2Character::TakeButtonReleased);
    InputComponent->BindAction("TakeObject", IE_Pressed, this,   &AProjet2Character::TakeButtonPressed);

	InputComponent->BindAction("Run", IE_Released, this,   &AProjet2Character::RunButtonReleased);
	InputComponent->BindAction("Run", IE_Pressed, this,   &AProjet2Character::RunButtonPressed);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this,   &AProjet2Character::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this,   &AProjet2Character::ZoomOut);
}


void AProjet2Character::OnResetVR()
{
	// If Projet2 is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Projet2.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProjet2Character::BeginPlay() {
	Super::BeginPlay();

	//ComponentSkeletalMesh = this->FindComponentByClass(new TSubclassOf<UActorComponent>::TClassType<USkeletalMeshComponent>);

	//Obtenir une référence vers le skeletal mesh de Joris
	TArray<USkeletalMeshComponent*> Components;
	this->GetComponents<USkeletalMeshComponent>(Components);

	if (Components.Num() > 0)
	{
		ComponentSkeletalMesh = Components[0];
	}
	
	if (ComponentSkeletalMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("ComponentSkeletalMesh found ! "));
		//Obtenir une référence vers l'anim instance de Joris
		AnimInstanceOfSkeletalMesh = dynamic_cast<UAnimationClassForJoris*>((ComponentSkeletalMesh)? ComponentSkeletalMesh->GetAnimInstance() : nullptr);
	}
	else {UE_LOG(LogTemp, Warning, TEXT("ComponentSkeletalMesh is empty ! "));}

	//Obtenir une référence vers le static mesh component du tonneau
	TArray<UStaticMeshComponent*> SComponents;
	this->GetComponents<UStaticMeshComponent>(SComponents);
	
	for (int i = 0; i < SComponents.Num(); i++)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Static mesh analyser : " + SComponents[i]->GetName()));
		
		
		if (SComponents[i]->GetName() == "StaticMeshTonneau")
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ComponentStaticMeshFound"));
			ComponentStaticMeshTonneau = SComponents[i];
			ComponentStaticMeshTonneau->SetHiddenInGame(true);
		}
	}

	//Obtenir une référence vers le camera boom
	TArray<USpringArmComponent*> CComponents;
	this->GetComponents<USpringArmComponent>(CComponents);

	if (CComponents.Num() > 0)
	{
		ComponentCameraBoom = CComponents[0];
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Component SpringArm Found"));
	}

	//Setup la valeur du camera arm
	FuturValueOfZoom = ComponentCameraBoom->TargetArmLength;
}

 
void AProjet2Character::TakeButtonReleased()
{
	
}

void AProjet2Character::TakeButtonPressed()
{
	isCarry = !isCarry;
	AnimInstanceOfSkeletalMesh->IsCarry = isCarry;

	if (isCarry)
	{
		//Afficher le tonneau
		ComponentStaticMeshTonneau->SetHiddenInGame(false);
		if (GetCharacterMovement()->Velocity.Size() > 300)
		{
			GetCharacterMovement()->MaxWalkSpeed = 300;
		}
	}
	else
	{
		//Cacher le tonneau
		ComponentStaticMeshTonneau->SetHiddenInGame(true);
	}
}

void AProjet2Character::RunButtonReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

void AProjet2Character::RunButtonPressed()
{
	if (!isCarry) // Si le joueur porte quelque chose il ne peut pas se mettre a courir. 
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}

void AProjet2Character::ZoomIn()
{
	if (ComponentCameraBoom->TargetArmLength > MinCameraZoom)
	{
		FuturValueOfZoom = ComponentCameraBoom->TargetArmLength - StepOfWheeling;
	}
}

void AProjet2Character::ZoomOut()
{
	if (ComponentCameraBoom->TargetArmLength < MaxCameraZoom)
	{
		FuturValueOfZoom = ComponentCameraBoom->TargetArmLength + StepOfWheeling;
	}
}

void AProjet2Character::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (ComponentCameraBoom->TargetArmLength != FuturValueOfZoom)
	{
		if (FuturValueOfZoom > ComponentCameraBoom->TargetArmLength)
		{
			ComponentCameraBoom->TargetArmLength += SpeedOfWheeling;
			if (FuturValueOfZoom <ComponentCameraBoom->TargetArmLength){FuturValueOfZoom = ComponentCameraBoom->TargetArmLength;}
		}
		if (FuturValueOfZoom < ComponentCameraBoom->TargetArmLength)
		{
			ComponentCameraBoom->TargetArmLength -= SpeedOfWheeling;
			if (FuturValueOfZoom >ComponentCameraBoom->TargetArmLength){FuturValueOfZoom = ComponentCameraBoom->TargetArmLength;}
		}
	}
}

void AProjet2Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AProjet2Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
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

void AProjet2Character::MoveRight(float Value)
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


