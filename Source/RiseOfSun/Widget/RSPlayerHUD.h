#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSPlayerHUD.generated.h"

class ARSPlayer;
class UTextBlock;

UCLASS()
class RISEOFSUN_API URSPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION()
    void OnEXPUpdated();

    // 헬퍼 함수
    FText GetAmmoText() const;

    // 델리게이트용 함수
    UFUNCTION()
    void UpdateAmmoText(int32 CurrentAmmo, int32 MaxAmmo);

protected:
    // 현재 표시할 HP
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerHUD")
    float DisplayHp = 0.0;

    // 현재 표시할 EXP
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerHUD")
    float DisplayEXP = 0.0;

    // **블루프린트 TextBlock과 바인딩**
    UPROPERTY(meta = (BindWidget))
    UTextBlock* AmmoTextBlock;

private:
    // 참조할 플레이어 캐릭터
    UPROPERTY()
    ARSPlayer* PlayerCharacter;
};
