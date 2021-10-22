// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimClassForAI.h"

UAnimClassForAI::UAnimClassForAI()
{
	
}

void UAnimClassForAI::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
	{
		fSpeed = OwningActor->GetVelocity().Size();
	}
}
