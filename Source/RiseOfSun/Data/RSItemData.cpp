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
    return !ItemID.IsNone() && !ItemName.IsEmpty();
}