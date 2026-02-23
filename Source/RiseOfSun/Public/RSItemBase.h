#pragma once

#include "CoreMinimal.h"
#include "RSItemData.h"
#include "UObject/NoExportTypes.h"
#include "RSItemBase.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RISEOFSUN_API URSItemBase : public UObject
{
	GENERATED_BODY()

public:
    URSItemBase();
    /** 아이템 기본 데이터 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FRSItemData ItemData;
    /** 아이템 초기화 */
    UFUNCTION(BlueprintCallable, Category = "Item")
    void SetItemData(const FRSItemData& Data);
    /** 공격력 반환 */
    UFUNCTION(BlueprintCallable, Category = "Item")
    int32 GetAttackPower() const;
    /** 무기 여부 */
    UFUNCTION(BlueprintCallable, Category = "Item")
    bool IsWeapon() const;
    /** 아이템 이름 반환 */
    UFUNCTION(BlueprintCallable, Category = "Item")
    FString GetItemName() const;
};
