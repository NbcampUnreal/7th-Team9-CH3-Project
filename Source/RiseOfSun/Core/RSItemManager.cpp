#include "RSItemManager.h"

#include "Data/RSItemData.h"
#include "Item/RSItemBase.h"

//정보제공 아이템 관리자 클래스 
FRSItemData URSItemManager::GetItemDataByID(FName ItemID) const
{
    if (!ItemDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemDataTable이 설정되지 않았습니다."));
        return FRSItemData();
    }
    static const FString ContextString(TEXT("Item Context"));
    FRSItemData* FoundData = ItemDataTable->FindRow<FRSItemData>(ItemID, ContextString);
    if (FoundData)
    {
        return *FoundData;
    }
    UE_LOG(LogTemp, Warning, TEXT("해당 ItemID가 DataTable에 없습니다: %s"), *ItemID.ToString());
    return FRSItemData();
}

URSItemBase* URSItemManager::SpawnItem(FName ItemID, UObject* Outer) 
{
    FRSItemData Data = GetItemDataByID(ItemID);
    if (!Data.IsValidItem())
    {
        UE_LOG(LogTemp, Warning, TEXT("유효하지 않은 아이템 ID: %s"), *ItemID.ToString());
        return nullptr;
    }

    URSItemBase* NewItem = NewObject<URSItemBase>(Outer);
    if (NewItem)
    {
        NewItem->SetItemData(Data);
    }
    return NewItem;
}
