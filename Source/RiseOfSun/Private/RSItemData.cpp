// Fill out your copyright notice in the Description page of Project Settings.


#include "RSItemData.h"
// 생성자나 유틸리티 함수가 없다면 지금은 아무것도 필요 없습니다.
// 하지만 확장용으로 아래처럼 메서드를 추가할 수 있습니다.
// 아이템 카테고리 이름을 FText로 반환
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