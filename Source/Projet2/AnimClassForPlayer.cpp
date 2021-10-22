// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimClassForPlayer.h"

UAnimClassForPlayer::UAnimClassForPlayer()
{
}


void UAnimClassForPlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
	{
		fSpeed = OwningActor->GetVelocity().Size();
	}
}
