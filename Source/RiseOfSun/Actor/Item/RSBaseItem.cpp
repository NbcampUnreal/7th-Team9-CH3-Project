// Fill out your copyright notice in the Description page of Project Settings.

//실제 객체를 담는 클래스(월드에 존재하는 아이템)(몸통)
#include "RSBaseItem.h"
#include "Engine/World.h"
#include "Actor/Character/Component/RSInventoryComponent.h" 
#include "Actor/Character/RSPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Item/RSItemBase.h"

ARSBaseItem::ARSBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. 최상위 루트 컴포넌트
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	// 2. 콜리전 설정 (Scene에 부착)
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene); // Scene에 직접 붙임

	// 3. 메시 설정 (Collision이 아닌 Scene에 부착)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);      // 중요: Collision 자식이 아니라 Scene의 자식으로!

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ARSBaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ARSBaseItem::OnItemEndOverlap);
}

void ARSBaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!")));
		ActivateItem(OtherActor);
	}
}

void ARSBaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
}

void ARSBaseItem::ActivateItem(AActor* Activator)
{
}

FName ARSBaseItem::GetItemType() const
{
	return FName();
}

void ARSBaseItem::DestroyItem()
{
	Destroy();
}

void ARSBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
    if (!ItemInstance)
    {
        ItemInstance = NewObject<URSItemBase>(this);
    }

    ItemInstance->SetItemData(Data);
}

// 이름 반환
FString ARSBaseItem::GetItemName() const
{
    return ItemInstance ? ItemInstance->GetItemName() : FString("None");
}

// 공격력 반환
int32 ARSBaseItem::GetAttackPower() const
{
    return ItemInstance ? ItemInstance->GetAttackPower() : 0;
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

void ARSBaseItem::Use(AActor* Activator)
{
	ActivateItem(Activator);
}

