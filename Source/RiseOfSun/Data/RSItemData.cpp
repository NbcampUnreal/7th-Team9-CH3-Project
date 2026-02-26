// Fill out your copyright notice in the Description page of Project Settings.


#include "RSItemData.h"

//아이템 도면 클래스
FText FRSItemData::GetCategoryAsText() const
{
    switch (Category)
    {
    case EItemCategory::Weapon:
        return FText::FromString("Weapon");
    case EItemCategory::Consumable:
        return FText::FromString("Consumable");
    case EItemCategory::Material:
        return FText::FromString("Material");
    default:
        return FText::FromString("Unknown");
    }
}
// 아이템 데이터 유효성 검사
bool FRSItemData::IsValidItem() const
{
    if (Category == EItemCategory::Weapon)
    {
        if (WeaponType == EWeaponType::None)
            return false;

        if (AttackPower <= 0)
            return false;

        // 무기는 보통 스택 불가
        if (MaxStack != 1)
            return false;
    }

    // 3️⃣ 스택형 아이템 검사
    if (Category == EItemCategory::Consumable ||
        Category == EItemCategory::Material)
    {
        if (MaxStack < 1)
            return false;

        if (DefaultStack < 1)
            return false;

        if (DefaultStack > MaxStack)
            return false;
    }
    return true;
}