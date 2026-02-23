#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSPlayer.h"
#include "RSPlayerHUD.generated.h"

UCLASS()
class RISEOFSUN_API URSPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION()
    void OnEXPUpdated();

protected:
    // 현재 표시할 HP
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerHUD")
    float DisplayHp = 0.0;

    // 현재 표시할 EXP
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerHUD")
    float DisplayEXP = 0.0;

private:
    // 참조할 플레이어 캐릭터
    UPROPERTY()
    ARSPlayer* PlayerCharacter;
};
