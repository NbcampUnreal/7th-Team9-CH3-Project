#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RSItemData.generated.h"

class ARSBaseItem;

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    Weapon,
    Consumable,
    Material
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    None,
    Rifle,
    MachineGun
};

USTRUCT(BlueprintType)
struct FRSItemData : public FTableRowBase
{
    GENERATED_BODY()

    

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName;

    

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    UTexture2D* Thumbnail; // 인벤토리에서 보여줄 아이템 썸네일

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    TSubclassOf<ARSBaseItem> ItemActorClass; // 아이템의 설계도, 아이템 드롭에서 사용

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemCategory Category;

    // 무기일 경우
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeaponType WeaponType = EWeaponType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AttackPower = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DefaultStack = 1;   // 생성 시 기본 수량

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStack = 1;       // 슬롯 최대 수량


    FText GetCategoryAsText() const;
    bool IsValidItem() const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf <AActor>ItemClass;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float SpawnChance;
};