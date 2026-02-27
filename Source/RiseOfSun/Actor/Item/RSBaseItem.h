// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Data/RSItemData.h"
#include "Item/ItemInterface.h"
#include "RSBaseItem.generated.h"

struct FRSItemData;
class URSItemBase;
class ARSPlayer;

UCLASS()
class RISEOFSUN_API ARSBaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	ARSBaseItem();

protected:
	//픽업 이벤트 연결 함수(OnpickedUp 호출)
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	USceneComponent* Scene;

	//충돌 영역 (픽업 감지용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	USphereComponent* Collision;

	//아이템 메시 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* Mesh;

	//실제 아이템 데이터 객체 
	UPROPERTY(VisibleAnywhere, Category = "Item")
	URSItemBase* ItemInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FRSItemData ItemData;

	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;

	virtual void DestroyItem();

public:	
	virtual void Tick(float DeltaTime) override;

	//아이템 데이터 초기화 
	void InitializeItem(const FRSItemData& Data);

	/** 아이템 이름 반환 */
	FString GetItemName() const;

	/** 공격력 반환 */
	int32 GetAttackPower() const;

	// 플레이어가 접근했을 때 호출
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnPickedUp(ARSPlayer* Player);

};
