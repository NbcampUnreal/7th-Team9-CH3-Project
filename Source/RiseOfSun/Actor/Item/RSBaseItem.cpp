// Fill out your copyright notice in the Description page of Project Settings.

//실제 객체를 담는 클래스(월드에 존재하는 아이템)(몸통)
#include "RSBaseItem.h"

#include "Item/RSItemBase.h"

ARSBaseItem::ARSBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);
	// 공통 메시 생성
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	// 메시를 루트로 사용
	//RootComponent = Mesh;
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


