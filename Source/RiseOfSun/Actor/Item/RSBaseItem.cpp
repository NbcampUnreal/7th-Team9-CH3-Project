// Fill out your copyright notice in the Description page of Project Settings.

//실제 객체를 담는 클래스(월드에 존재하는 아이템)(몸통)
#include "RSBaseItem.h"
#include "Actor/Character/Component/RSInventoryComponent.h" 
#include "Actor/Character/RSPlayer.h"
#include "Item/RSItemBase.h"

ARSBaseItem::ARSBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	// 공통 메시 생성
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// 메시를 루트로 사용
	RootComponent = Mesh;
}

void ARSBaseItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (ARSPlayer* Player = Cast<ARSPlayer>(OtherActor))
	{
		OnPickedUp(Player);
	}
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

// 플레이어가 접근했을 때 호출
void ARSBaseItem::OnPickedUp(ARSPlayer* Player)
{
	if (!Player || !Player->GetInventoryComponent()) return;

	// 플레이어 인벤토리에 아이템 추가
	bool bAdded = Player->GetInventoryComponent()->AddItem(ItemData.ItemID, ItemData.DefaultStack);

	if (bAdded)
	{
		// 추가 성공하면 월드에서 삭제
		Destroy();
	}
	else
	{
		// 실패 시 로그 출력
		UE_LOG(LogTemp, Warning, TEXT("인벤토리 꽉참! 아이템 [%s] 추가 실패"), *ItemData.ItemID.ToString());
	}
}

