#include "RSItemManager.h"
#include "Data/RSItemData.h"
#include "Item/RSItemBase.h"

//정보제공 아이템 관리자 클래스 
FRSItemData URSItemManager::GetItemDataByID(FName ItemID) const
{
    if (!ItemDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemDataTable이 비어 있음."));
        return FRSItemData();
    }
    static const FString ContextString(TEXT("Item Context"));
    FRSItemData* Row = ItemDataTable->FindRow<FRSItemData>(ItemID, ContextString);
    if (!Row)
    {
        UE_LOG(LogTemp, Error, TEXT("ItemID '%s' 없음"), *ItemID.ToString());
        return FRSItemData();
    }
    return *Row;
}

URSItemBase* URSItemManager::SpawnItem(FName ItemID, UObject* Outer)
{
    FRSItemData Data = GetItemDataByID(ItemID);
    if (!Data.IsValidItem())
    {
        UE_LOG(LogTemp, Warning, TEXT("유효하지 않은 아이템 ID: %s"), *ItemID.ToString());
        return nullptr;
    }
    if (!Outer)
    {
        UE_LOG(LogTemp, Warning, TEXT("Outer 없음 → GetTransientPackage 사용"));
        Outer = GetTransientPackage();
    }
    URSItemBase* NewItem = NewObject<URSItemBase>(Outer);
    if (NewItem)
    {
        NewItem->SetItemData(Data);
    }
    return NewItem;
}
