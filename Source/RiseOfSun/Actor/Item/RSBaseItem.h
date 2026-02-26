// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Data/RSItemData.h"
#include "RSBaseItem.generated.h"

class URSItemBase;

UCLASS()
class RISEOFSUN_API ARSBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSBaseItem();

	// 월드 정보
	UPROPERTY(Transient)
	class UWorld* World;
	UPROPERTY()
	class URSInventoryComponent* OwningInventory;


protected:
	//충돌 영역 (픽업 감지용)
	UPROPERTY(VisibleAnywhere, Category = "Item")
	USphereComponent* Collision;

	//아이템 메시 
	UPROPERTY(VisibleAnywhere, Category = "Item")
	UStaticMeshComponent* Mesh;

	//실제 아이템 데이터 객체 
	UPROPERTY(VisibleAnywhere, Category = "Item")
	URSItemBase* ItemInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FRSItemData ItemData;
public:	

	//아이템 데이터 초기화 
	void InitializeItem(const FRSItemData& Data);

	/** 아이템 이름 반환 */
	FString GetItemName() const;

	/** 공격력 반환 */
	int32 GetAttackPower() const;


};
