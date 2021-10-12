// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationClassForJoris.h"

UAnimationClassForJoris::UAnimationClassForJoris()
{
}


void UAnimationClassForJoris::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
	{
		Speed = OwningActor->GetVelocity().Size();
	}
}
