#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/RSItemData.h"
#include "RSInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Slot")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Slot")
	int32 StackCount; // 현재 슬롯에 몇 개 들어있는지
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdatedSlot, TArray<FInventorySlot>, Slots);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RISEOFSUN_API URSInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URSInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	// 아이템슬롯을 TArray배열로 만들어서 여러 슬롯을 가진 아이템 배열 완성
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Inventory")
	TArray<FInventorySlot> Items;
	
	// 인벤토리 크기
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 InventorySize = 10;

	// 아이템 추가
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FName ItemID, int32 Count = 1);

	// 아이템 제거
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(FName ItemID, int32 Count = 1);

	// 슬롯 초기화
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeSlots();


	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdatedSlot OnInventoryUpdated;
};
