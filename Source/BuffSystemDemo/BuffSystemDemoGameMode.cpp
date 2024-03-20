// Copyright Epic Games, Inc. All Rights Reserved.

#include "BuffSystemDemoGameMode.h"
#include "BuffSystemDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABuffSystemDemoGameMode::ABuffSystemDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
