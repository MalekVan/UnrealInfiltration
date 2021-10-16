// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "AnimationClassForJoris.generated.h"

/**
 * 
 */

UCLASS(Transient, Blueprintable, HideCategories = AnimInstance, BlueprintType)
class PROJET2_API UAnimationClassForJoris : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAnimationClassForJoris();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	bool IsCarry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
	bool IsSitting;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
    bool bWon;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InfosOwner")
    bool bLost;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
