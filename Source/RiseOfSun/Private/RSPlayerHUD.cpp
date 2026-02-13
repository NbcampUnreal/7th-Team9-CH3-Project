#include "RSPlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void URSPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();
	PlayerCharacter = nullptr;

    // 플레이어 캐릭터 가져오기
    PlayerCharacter = Cast<ARSPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (PlayerCharacter)
    {
        DisplayHp = PlayerCharacter->GetCurrentHp(); // C++ 플레이어 클래스에 CurrentHp가 있어야 함
    }
}

void URSPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!PlayerCharacter) return;

    // 현재 HP 가져오기
    float TargetHp = PlayerCharacter->GetCurrentHp();

    // 보간해서 DisplayHp 갱신
    DisplayHp = FMath::FInterpTo(DisplayHp, TargetHp, InDeltaTime, 7.0f);
}
