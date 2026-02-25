#include "RSFoodItem.h"
#include "Actor/Character/RSPlayer.h"

void URSFoodItem::Use(ARSPlayer* Player)
{
    if (Player)
    {
        Player->Stat.CurrentHealth += HealthToHeal;
    }
}
