// Copyright Epic Games, Inc. All Rights Reserved.

#include "kadaiProjectGameMode.h"
#include "kadaiProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AkadaiProjectGameMode::AkadaiProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
