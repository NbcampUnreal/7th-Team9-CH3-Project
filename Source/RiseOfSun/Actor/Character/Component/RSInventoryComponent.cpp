#include "RSInventoryComponent.h"
#include "Item/RSItemBase.h"
#include "Blueprint/UserWidget.h"
#include "Actor/Character/RSPlayer.h"

URSInventoryComponent::URSInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URSInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    // 슬롯 초기화
    InitializeSlots();
}

//아이템 추가
bool URSInventoryComponent::AddItem(FName ItemID, int32 Count)
{
    if (ItemID == NAME_None || Count <= 0)
        return false;

    // 같은 아이템 있으면 스택 증가 (선택 사항)
    for (FInventorySlot& Slot : Items)
    {
        if (Slot.ItemID == ItemID)
        {
            Slot.StackCount += Count;
            OnInventoryUpdated.Broadcast(Items);
            return true;
        }
    }

    // 빈 슬롯 찾기
    for (FInventorySlot& Slot : Items)
    {
        if (Slot.ItemID == NAME_None)
        {
            Slot.ItemID = ItemID;
            Slot.StackCount = Count;

            if (GEngine)
            {
                FString Msg = FString::Printf(TEXT("아이템 [%s] %d개 추가"), *ItemID.ToString(), Count);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Msg);
            }

            OnInventoryUpdated.Broadcast(Items);
            return true;
        }
    }

    // 슬롯 부족
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("[비상!] 인벤토리가 모두 찼습니다!"));

    return false;
}

//아이템 제거
bool URSInventoryComponent::RemoveItem(FName ItemID, int32 Count)
{
    if (ItemID == NAME_None || Count <= 0) return false;

    for (FInventorySlot& Slot : Items)
    {
        if (Slot.ItemID == ItemID)
        {
            if (Slot.StackCount > Count)
            {
                Slot.StackCount -= Count;
            }
            else
            {
                Slot.StackCount = 0;
                Slot.ItemID = NAME_None;
            }

            OnInventoryUpdated.Broadcast(Items);
            return true;
        }
    }

    return false;
}

//슬롯 초기화
void URSInventoryComponent::InitializeSlots()
{
    Items.SetNum(InventorySize);
    for (int32 i = 0; i < Items.Num(); i++)
    {
        Items[i].ItemID = NAME_None;
        Items[i].StackCount = 0;
    }

    OnInventoryUpdated.Broadcast(Items);
}
