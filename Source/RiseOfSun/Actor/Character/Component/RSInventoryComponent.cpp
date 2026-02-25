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

    Items.SetNum(InventorySize); // 인벤토리 크기를 InventorySize인 10만큼 생성합니다


}

void URSInventoryComponent::AddItem(FName ItemID)
{
    if (ItemID == NAME_None)
    {
        return;
    }

    for (int32 i = 0; i < Items.Num(); i++)
    {
        if (Items[i].ItemID == NAME_None)
        {
            Items[i].ItemID = ItemID;

            if (GEngine)
            {
                FString const Msg = FString::Printf(TEXT("아이템 저장! [ %d번 ] 슬롯에 [ %s ] 저장!"), i, *ItemID.ToString());
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Msg);
            }

            return;
        }
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("[비상!] 인벤토리가 모두 찼습니다!"));
    }
}