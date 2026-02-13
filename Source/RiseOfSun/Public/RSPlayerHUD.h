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

protected:
    // 현재 표시할 HP
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerHUD")
    double DisplayHp = 0.0;

private:
    // 참조할 플레이어 캐릭터
    UPROPERTY()
    ARSPlayer* PlayerCharacter;
};
