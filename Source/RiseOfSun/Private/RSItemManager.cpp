#include "RSItemManager.h"

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
