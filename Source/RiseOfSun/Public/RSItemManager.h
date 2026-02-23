#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RSItemData.h"
#include "RSItemBase.h"
#include "UObject/NoExportTypes.h"
#include "RSItemManager.generated.h"

//아이템 데이터를 전역적으로 관리하는 매니저 클래스
UCLASS(BlueprintType, Blueprintable)
class RISEOFSUN_API URSItemManager : public UObject
{
	GENERATED_BODY()
	
public:
    /** 아이템 데이터 테이블 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UDataTable* ItemDataTable;
public:
    /** DataTable에서 ID로 데이터 불러오기 */
    UFUNCTION(BlueprintCallable, Category = "Item")
    FRSItemData GetItemDataByID(FName ItemID) const;
    UFUNCTION(BlueprintCallable)
    URSItemBase* SpawnItem(FName ItemID, UObject* Outer);
};