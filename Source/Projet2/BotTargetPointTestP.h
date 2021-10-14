// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "BotTargetPointTestP.generated.h"

/**
 * 
 */
UCLASS()
class PROJET2_API ABotTargetPointTestP : public ATargetPoint
{
	GENERATED_BODY()
	public : 
	ABotTargetPointTestP();

	//BOX COLLISION NE MARCHE PAS EN JEU, POURQUOI ?????? NAPPARAIT MEME PAS DANS LA VUE EN JEU
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Collider")
	class UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	class UStaticMeshComponent* SocleMesh;
	
	bool FruitOnThisTargetPoint = false;
};
