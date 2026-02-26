#include "RSPlayerHUD.h"

#include "Actor/Character/RSPlayer.h"
#include "Actor/Character/Component/RSRifleComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PanelWidget.h"
#include "Misc/OutputDeviceNull.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Actor/Character/Component/RSInventoryComponent.h"

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
    if (!InventoryGrid || !PlayerCharacter) return;

    InventoryGrid->ClearChildren();

    const int32 MaxColumns = 5; // 가로 5칸

    for (int32 i = 0; i < Slots.Num(); i++)
    {
        const FInventorySlot& InventorySlot = Slots[i];

        if (InventorySlotWidgetClass)
        {
            UUserWidget* SlotWidget =
                CreateWidget<UUserWidget>(GetWorld(), InventorySlotWidgetClass);

            if (SlotWidget)
            {
                // 🔹 Grid 위치 계산
                int32 Row = i / MaxColumns;
                int32 Column = i % MaxColumns;

                UGridSlot* GridSlot = InventoryGrid->AddChildToGrid(SlotWidget);
                GridSlot->SetRow(Row);
                GridSlot->SetColumn(Column);

                // 🔹 아이템 데이터 전달
                FOutputDeviceNull Ar;
                FString Cmd = FString::Printf(
                    TEXT("SetItemData %s %d"),
                    *InventorySlot.ItemID.ToString(),
                    InventorySlot.StackCount
                );

                SlotWidget->CallFunctionByNameWithArguments(*Cmd, Ar, nullptr, true);
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Inventory UI Updated!"));
}

//껐다 켰다 하는 기능.
void URSPlayerHUD::ToggleInventory()
{
    if (!InventoryPanel) return;

    bInventoryVisible = !bInventoryVisible;
    
    InventoryPanel->SetVisibility(
        bInventoryVisible ? ESlateVisibility::Visible
        : ESlateVisibility::Hidden
    );
}
