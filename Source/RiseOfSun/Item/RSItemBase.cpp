#include "RSItemBase.h"

//FRSItemData에 정의된 정보를 담는 실제 객체 클래스 = 아이템 정보만 있는 논리 객체 클래스(두뇌)

URSItemBase::URSItemBase()
{
    ItemDisplayName = FText::FromString("Item");
    UseActionText = FText::FromString("Use");
}

// 데이터 세팅
void URSItemBase::SetItemData(const FRSItemData& Data)
{
    ItemData = Data;
    StackCount = Data.DefaultStack;
}

// 공격력 반환
int32 URSItemBase::GetAttackPower() const
{
    return ItemData.AttackPower;
}

// 무기 여부
bool URSItemBase::IsWeapon() const
{
    return ItemData.Category == EItemCategory::Weapon;
}

FName URSItemBase::GetItemID() const
{
    return ItemData.ItemID;
}

// 아이템 이름 반환
FString URSItemBase::GetItemName() const
{
    return ItemData.ItemName;
}

bool URSItemBase::IsStackable() const
{
    return ItemData.MaxStack > 1;
}
