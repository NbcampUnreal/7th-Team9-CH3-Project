// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameInstance.h"
#include "Engine/Engine.h" //GEngine 사용
#include "GameFramework/GameUserSettings.h" // UGameUserSettings 헤더 포함

void URSGameInstance::Init()
{
    Super::Init();

    if (GEngine)
    {
        UGameUserSettings* Settings = GEngine->GetGameUserSettings();

        if (Settings)
        {
            Settings->LoadSettings(false);

            // Saved 폴더에 유저 설정이 이미 있는지 체크
            const bool bHasUserSettings =
                Settings->GetLastConfirmedScreenResolution().X > 0;

            if (!bHasUserSettings)
            {
                // 모니터 최대 해상도 가져오기
                FIntPoint DesktopRes = Settings->GetDesktopResolution();

                Settings->SetScreenResolution(DesktopRes);
                Settings->SetFullscreenMode(EWindowMode::Fullscreen);

                Settings->ApplySettings(true);
                Settings->SaveSettings();
            }
            else
            {
                // 기존 설정 유지
                Settings->ApplySettings(false);
            }
        }
    }
}
