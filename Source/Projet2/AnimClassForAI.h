// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "AnimClassForAI.generated.h"

/**
 * 
 */
UCLASS(Transient, Blueprintable, HideCategories = AnimInstance, BlueprintType)
class PROJET2_API UAnimClassForAI : public UAnimInstance
{
	GENERATED_BODY()
	
	public :

	UAnimClassForAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	float fSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	bool bIsCarry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	bool bIsSitting;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	bool bWon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	bool bLost;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
