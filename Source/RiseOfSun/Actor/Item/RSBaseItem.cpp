// Fill out your copyright notice in the Description page of Project Settings.

//실제 객체를 담는 클래스(월드에 존재하는 아이템)(몸통)
#include "RSBaseItem.h"

#include "Item/RSItemBase.h"

ARSBaseItem::ARSBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	// 공통 메시 생성
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// 메시를 루트로 사용
	RootComponent = Mesh;
}

// 데이터 초기화
void ARSBaseItem::InitializeItem(const FRSItemData& Data)
{
	ItemData = Data;
}

// 이름 반환
FString ARSBaseItem::GetItemName() const
{
	if (ItemData.IsValidItem())
	{
		return ItemData.ItemName;
	}
	return FString("None");
}

// 공격력 반환
int32 ARSBaseItem::GetAttackPower() const
{
	if (ItemData.IsValidItem())
	{
		return ItemData.AttackPower;
	}
	return 0;
}

