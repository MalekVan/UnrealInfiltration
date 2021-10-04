// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projet2GameMode.h"
#include "Projet2Character.h"
#include "UObject/ConstructorHelpers.h"

AProjet2GameMode::AProjet2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
