// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimClassForPlayer.h"
#include "Chair.h"
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
	
	static float GetDistanceBetweenVectors(FVector From, FVector To);
	
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
	UAnimClassForPlayer * AnimInstanceOfSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* ComponentCameraBoom;
	
	ACollectible* HoldedCollectible = nullptr;
	AChair* LevelChair = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCarry;
	
	bool bCanMove = true;

protected:
	
	virtual void BeginPlay() override;

	//Controller
	void UpdateMovementState();

	void RunButtonReleased();
	void RunButtonPressed();

	void ZoomIn();
	void ZoomOut();

	//CAMERA VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iMaxCameraZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iMinCameraZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iStepOfWheeling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iSpeedOfWheeling;

	float fFuturValueOfZoom;

	virtual void Tick(float DeltaTime) override;

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

