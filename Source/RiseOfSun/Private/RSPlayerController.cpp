// Fill out your copyright notice in the Description page of Project Settings.


#include "RSPlayerController.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"

void ARSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 로컬 플레이어에서만 실행
    if (IsLocalController())
    {
        if (GEngine)
        {
            UGameUserSettings* Settings = GEngine->GetGameUserSettings();
            if (Settings)
            {
                Settings->SetScreenResolution(FIntPoint(1920, 1080));
                Settings->SetFullscreenMode(EWindowMode::Windowed);
                Settings->ApplySettings(true);
                Settings->SaveSettings();
            }
        }
    }
}