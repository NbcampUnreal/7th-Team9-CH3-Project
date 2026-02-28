#include "RSPlayerHUD.h"

#include "Actor/Character/RSPlayer.h"
#include "Actor/Character/Component/RSRifleComponent.h"
#include "InventorySlotWidget.h"
#include "InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Character/Component/RSInventoryComponent.h"
#include "Core/RSGameInstance.h"

void URSPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();
    // 플레이어 캐릭터 가져오기
    PlayerCharacter = Cast<ARSPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (PlayerCharacter)
    {
        DisplayHp = PlayerCharacter->GetCurrentHP();
        DisplayEXP = PlayerCharacter->GetCurrentEXP();
        // EXP 델리게이트 바인딩
        PlayerCharacter->OnEXPChanged.AddDynamic(this, &URSPlayerHUD::OnEXPUpdated);
        // 탄약 델리게이트 바인딩
        if (URSRifleComponent* Rifle = PlayerCharacter->FindComponentByClass<URSRifleComponent>())
        {
            Rifle->OnAmmoChanged.AddDynamic(this, &URSPlayerHUD::UpdateAmmoText);
            UpdateAmmoText(Rifle->AmmoInClip, Rifle->MaxAmmoInClip);
        }

        UE_LOG(LogTemp, Warning, TEXT("HUD Constructed: %s"), *GetNameSafe(this));
    }

// 인벤토리 델리게이트 바인딩
    if (PlayerCharacter)
    {
        InventoryComponent = PlayerCharacter->FindComponentByClass<URSInventoryComponent>();
        if (InventoryComponent)
        {
            InventoryWidget->InitSlot(InventoryComponent->InventorySize);
            InventoryComponent->OnInventoryUpdated.AddDynamic(
                this,
                &URSPlayerHUD::UpdateInventoryUI
            );

            InventoryComponent->InitializeSlots();
        }
    }

}
void URSPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (!PlayerCharacter) return;
    // Rifle 보정 처리 (뒤늦게 붙었을 때도 델리게이트 자동 등록)
    if (!bAmmoBound && PlayerCharacter)
    {
        if (URSRifleComponent* Rifle = PlayerCharacter->FindComponentByClass<URSRifleComponent>())
        {
            if (!Rifle->OnAmmoChanged.IsBound())
            {
                Rifle->OnAmmoChanged.AddDynamic(this, &URSPlayerHUD::UpdateAmmoText);
                UpdateAmmoText(Rifle->AmmoInClip, Rifle->MaxAmmoInClip);
                bAmmoBound = true;
            }
        }
    }
    // HP / EXP 보간 갱신
    DisplayHp = FMath::FInterpTo(DisplayHp, PlayerCharacter->GetCurrentHP(), InDeltaTime, 7.0f);
    DisplayEXP = FMath::FInterpTo(DisplayEXP, PlayerCharacter->GetCurrentEXP(), InDeltaTime, 7.0f);
}
void URSPlayerHUD::OnEXPUpdated()
{
    if (!PlayerCharacter) return;
    DisplayEXP = PlayerCharacter->GetCurrentEXP();
}
FText URSPlayerHUD::GetAmmoText() const
{
    APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!Pawn) return FText::FromString("0 / 0");

    URSRifleComponent* Rifle = Pawn->FindComponentByClass<URSRifleComponent>();
    if (!Rifle) return FText::FromString("0 / 0");

    const FString AmmoString = FString::Printf(TEXT("%d / %d"), Rifle->AmmoInClip, Rifle->MaxAmmoInClip);
    return FText::FromString(AmmoString);
}
void URSPlayerHUD::UpdateAmmoText(int32 CurrentAmmo, int32 MaxAmmo)
{
    if (!AmmoTextBlock) return;
    const FString AmmoString = FString::Printf(TEXT("%d / %d"), CurrentAmmo, MaxAmmo);

    AmmoTextBlock->SetText(FText::FromString(AmmoString));
    UE_LOG(LogTemp, Log, TEXT("Ammo UI Updated: %s"), *AmmoString);
}

void URSPlayerHUD::UpdateInventoryUI(TArray<FInventorySlot> Slots)
{
    if (!InventoryWidget) return;
    URSGameInstance* RSGameInstance = Cast<URSGameInstance>(GetGameInstance());
    if (!RSGameInstance) return;
    
    check(RSGameInstance->ItemManager);

    URSItemManager* ItemManager = RSGameInstance->ItemManager;
    for (int32 i = 0; i < Slots.Num(); i++)
    {
        const FInventorySlot& InventorySlot = Slots[i];
        const FRSItemData& ItemData = ItemManager->GetItemDataByID(InventorySlot.ItemID);
        InventoryWidget->SetItemByIndex(i, ItemData.Thumbnail, InventorySlot.StackCount);
    }

    UE_LOG(LogTemp, Log, TEXT("Inventory UI Updated!"));
}

//껐다 켰다 하는 기능.
void URSPlayerHUD::ToggleInventory()
{
    bInventoryVisible = !bInventoryVisible;
    if (InventoryWidget)
    {
        InventoryWidget->SetVisibilityWithBool(bInventoryVisible);
    }
}
