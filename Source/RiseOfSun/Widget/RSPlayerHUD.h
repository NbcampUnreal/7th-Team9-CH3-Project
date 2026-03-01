#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "RSPlayerHUD.generated.h"

class UInventoryWidget;
class ARSPlayer;
class URSInventoryComponent;
class UPanelWidget;
class UUserWidget;
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

    UFUNCTION()
    void UpdateCurrentZombie(int32 SpawnZombie, int32 ZombieKillCount);

    UFUNCTION()
    void ToggleInventory();

    // 인벤토리 UI 갱신 함수
    UFUNCTION()
    void UpdateInventoryUI(TArray<FInventorySlot> Slots);
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
    
    UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "Inventory")
    UInventoryWidget* InventoryWidget;

    UPROPERTY()
    URSInventoryComponent* InventoryComponent;

    // 슬롯 위젯 클래스 (블루프린트에서 지정)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<UUserWidget> InventorySlotWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Zombie;

private:
    // 참조할 플레이어 캐릭터
    UPROPERTY()
    ARSPlayer* PlayerCharacter;

    bool bAmmoBound = false;

    UPROPERTY()
    bool bInventoryVisible = false;

    bool bZombieBound = false;
};
