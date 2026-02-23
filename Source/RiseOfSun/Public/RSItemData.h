// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RSItemData.generated.h"

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
struct FRSItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemCategory Category;

    // 무기일 경우
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeaponType WeaponType = EWeaponType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AttackPower = 0;

    // 소모품 개수용
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StackCount = 1;

    // --- 확장 기능 ---
    FText GetCategoryAsText() const;
    bool IsValidItem() const;
};