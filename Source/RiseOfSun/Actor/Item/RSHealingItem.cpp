#include "Actor/Item/RSHealingItem.h"

ARSHealingItem::ARSHealingItem()
{
    HealAmount = 100.0f;
    ItemType = "Healing";
}

void ARSHealingItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Green,
            FString::Printf(TEXT("Player gained %f HP"), HealAmount));
        DestroyItem();
    }
}
