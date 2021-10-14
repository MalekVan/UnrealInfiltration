// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimationClassForJoris.h"
#include "Collectible.h"
#include "GameFramework/Character.h"
#include "Projet2Character.generated.h"

UCLASS(config=Game)
class AProjet2Character : public ACharacter
{
	GENERATED_BODY()
		
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AProjet2Character();
	
	//class UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* ComponentSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimationClassForJoris * AnimInstanceOfSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* ComponentCameraBoom;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();
	
	virtual void BeginPlay() override;

	//Controller
	void UpdateMovementState();

	void RunButtonReleased();
	void RunButtonPressed();

	void ZoomIn();
	void ZoomOut();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isCarry;

	ACollectible* HoldedCollectible = nullptr;

	//CAMERA VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCameraZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinCameraZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StepOfWheeling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpeedOfWheeling;

	float FuturValueOfZoom;

	virtual void Tick(float deltaTime) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	
	void Interact();

	static float GetDistanceBetweenVectors(FVector From, FVector To);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	class AProjet2GameMode* GameMode;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

