// Fill out your copyright notice in the Description page of Project Settings.


#include "RSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"



void ARSPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    const FString LevelName = GetWorld()->GetName();
    if (LevelName.Contains(TEXT("MainLevel")))
    {
        if (StartMenuClass)
        {
            StartMenu = CreateWidget<UUserWidget>(this, StartMenuClass);
            if (StartMenu)
            {
                StartMenu->AddToViewport(0);

                SetInputMode(FInputModeUIOnly());
                bShowMouseCursor = true;
            }
        }
    }
    if (LevelName.Contains(TEXT("TestLevel")))
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }

    if (HUDWidgetClass)
    {
        UUserWidget* RSHUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);
        if (RSHUDWidget)
        {
            RSHUDWidget->AddToViewport();
        }
    }
}

