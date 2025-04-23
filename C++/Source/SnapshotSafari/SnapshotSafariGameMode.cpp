// Copyright Epic Games, Inc. All Rights Reserved.

#include "SnapshotSafariGameMode.h"
#include "SnapshotSafariCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASnapshotSafariGameMode::ASnapshotSafariGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
