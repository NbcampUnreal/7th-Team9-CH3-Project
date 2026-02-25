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
};

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

	// 인벤토리를 시각화 하기위해서 어떤 위젯을 사용할지 담는 변수
	UPROPERTY(EditAnywhere, Category = "Inventory|UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	
	// 우리가 아까 만든 데이터 테이블을 저장할 변수 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|UI")
	UDataTable* ItemDataTable;

	// 아이템 줍는 함수, 위젯 블루프린트에서 호출(BlueprintCallable)
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(FName ItemID);
};
