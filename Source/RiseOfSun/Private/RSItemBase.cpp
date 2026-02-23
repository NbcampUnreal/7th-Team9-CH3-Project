#include "RSItemBase.h"

URSItemBase::URSItemBase()
{
    // 필요 시 기본값 세팅 가능
}
void URSItemBase::InitializeItem(const FRSItemData& Data)
{
    ItemData = Data;
}
int32 URSItemBase::GetAttackPower() const
{
    return ItemData.AttackPower;
}
bool URSItemBase::IsWeapon() const
{
    return ItemData.Category == EItemCategory::Weapon;
}
FString URSItemBase::GetItemName() const
{
    return ItemData.ItemName;
}