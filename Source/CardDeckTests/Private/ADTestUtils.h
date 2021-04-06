#pragma once

#include "CoreMinimal.h"

#include "UnrealClient.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

class FADTestUtils
{
public:
	static const int32 TestsFlags = EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter;

	static UWorld* GetWorld()
	{
		if (GEngine)
		{
			if (FWorldContext* WorldContext = GEngine->GetWorldContextFromPIEInstance(0))
			{
				return WorldContext->World();
			}
		}

		return nullptr;
	}

	static void Exit()
	{
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* TargetPC = UGameplayStatics::GetPlayerController(World, 0))
			{
				TargetPC->ConsoleCommand(TEXT("Exit"), true);
			}
		}
	}

	static bool PressKey(const FName& KeyName, EInputEvent InputEvent)
	{
		if (GEngine && GEngine->GameViewport)
		{
			if (FViewport* Viewport = GEngine->GameViewport->Viewport)
			{
				if (FViewportClient* ViewportClient = Viewport->GetClient())
				{
					return ViewportClient->InputKey(FInputKeyEventArgs(Viewport, 0, KeyName, InputEvent));
				}
			}
		}

		return false;
	}

};
