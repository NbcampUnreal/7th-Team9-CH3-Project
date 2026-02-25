#include "RSInventoryComponent.h"
#include "Item/RSItemBase.h"

URSInventoryComponent::URSInventoryComponent()
{
	Capacity = 20;

}

bool URSInventoryComponent::AddItem(URSItemBase* Item)
{	
	//널 포인터 방지
	if (!Item)
		return false;

	int32 RemainingStack = Item->StackCount;

	// ① 기존 슬롯 먼저 채우기 (이중 for 제거)
	for (URSItemBase* ExistingItem : Items)
	{
		if (!ExistingItem)
			continue;

		if (ExistingItem->GetItemID() == Item->GetItemID() &&
			ExistingItem->IsStackable())
		{
			int32 MaxStack = ExistingItem->ItemData.MaxStack;
			int32 SpaceLeft = MaxStack - ExistingItem->StackCount;

			if (SpaceLeft <= 0)
				continue;

			int32 AddAmount = FMath::Min(SpaceLeft, RemainingStack);

			ExistingItem->StackCount += AddAmount;
			RemainingStack -= AddAmount;

			if (RemainingStack <= 0)
			{
				OnInventoryUpdated.Broadcast();
				return true;
			}
		}
	}

	// 인벤토리 용량 제한, 아이템인지 확인
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	OnInventoryUpdated.Broadcast();

	return true;
}

bool URSInventoryComponent::RemoveItem(URSItemBase* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}



void URSInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}

}



