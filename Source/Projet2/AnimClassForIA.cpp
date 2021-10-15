// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimClassForIA.h"

UAnimClassForIA::UAnimClassForIA()
{
	
}

void UAnimClassForIA::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
	{
		Speed = OwningActor->GetVelocity().Size();
	}
}
