// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameInstance.h"
#include "RSItemManager.h"
#include "Engine/Engine.h" //GEngine 사용
#include "GameFramework/GameUserSettings.h" // UGameUserSettings 헤더 포함
#include "Item/RSItemBase.h"

// 전역 매니저를 보관할 클래스
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
    //UPROPERTY에 연결된 매니저 생성 (GC 추적 보장)
    // GameInstance Init()에서 한 번 실행됨
    ItemManager = NewObject<URSItemManager>(this);
    ItemManager->ItemDataTable = LoadObject<UDataTable>(
        nullptr,
        TEXT("/Game/Data/DT_ItemData.DT_ItemData")
    );
    if (!ItemManager->ItemDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("아이템 데이터 테이블 로드 실패!"));
        return;
    }
    // 테스트용 데이터 로드
    if (ItemManager && ItemManager->ItemDataTable)
    {
        //RowName -> 데이터 테이블에서 맞춤
        URSItemBase* RifleItem = ItemManager->SpawnItem(FName("Rifle"), this);
        if (RifleItem)
        {
            UE_LOG(LogTemp, Log, TEXT("아이템 이름: %s, 공격력: %d"),
                *RifleItem->GetItemName(),
                RifleItem->GetAttackPower());
        }
    }
}
