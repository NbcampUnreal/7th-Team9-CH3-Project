#include "Actor/Item/RSHealingItem.h"
#include "Actor/Character/RSPlayer.h"
#include "Engine/Engine.h"

ARSHealingItem::ARSHealingItem()
{
    HealAmount = 100.0f;
    ItemType = "Healing";
    ItemData.ItemID = FName("Heal");
}

void ARSHealingItem::ActivateItem(AActor* Activator)
{
    if (!Activator) return;

    // 1. 플레이어 캐릭터인지 확인
    ARSPlayer* Player = Cast<ARSPlayer>(Activator);

    // 2. 플레이어고, 태그가 Player라면 (안정성을 위해 체크)
    if (Player && Player->ActorHasTag("Player"))
    {
        // 3. 인벤토리에 추가 시도!
        // ItemID는 "Heal" 같은 식별자
        Player->PickUpItem(FName("Heal"), 1);

        DestroyItem();
    }
}
