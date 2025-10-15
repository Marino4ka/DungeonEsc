// Copyright Epic Games, Inc. All Rights Reserved.


#include "DungeonEscapePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "DungeonEscapeCameraManager.h"

ADungeonEscapePlayerController::ADungeonEscapePlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ADungeonEscapeCameraManager::StaticClass();
}

void ADungeonEscapePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
