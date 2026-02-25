#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RSInventoryComponent.generated.h"

// UI 업데이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RISEOFSUN_API URSInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URSInventoryComponent();

	// 아이템 추가
	bool AddItem(class URSItemBase* Item);
	// 아이템 제거
	bool RemoveItem(class URSItemBase* Item);
	// 기본적으로 주어지는 아이템
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class URSItemBase*> DefaultItems;
	// 아이템 개수
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;
	// 인벤토리에 있는 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class URSItemBase*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



};
