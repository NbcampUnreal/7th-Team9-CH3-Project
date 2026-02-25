#pragma once

#include "CoreMinimal.h"
#include "Data/RSItemData.h"
#include "RSItemBase.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RISEOFSUN_API URSItemBase : public UObject
{
	GENERATED_BODY()

public:
    URSItemBase();

    virtual class UWorld* GetWorld() const { return World; };

    // 월드 정보
    UPROPERTY(Transient)
    class UWorld* World;
    // 문구 표시
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText UseActionText;
    // 줍기 기능
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    class UStaticMesh* PickupMesh;
    // 아이템 섬네일
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    class UTexture2D* Thumbnail;
    // 아이템 이름 표시
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemDisplayName;
    UPROPERTY()
    class URSInventoryComponent* OwningInventory;
    
    virtual void Use(class ARSPlayer* Player) PURE_VIRTUAL(UItem, );

    UFUNCTION(BlueprintImplementableEvent)
    void OnUse(class ARSPlayer* Player);

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
