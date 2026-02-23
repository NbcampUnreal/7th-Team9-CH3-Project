#include "RSInventoryComponent.h"
#include "RSBaseItem.h"

URSInventoryComponent::URSInventoryComponent()
{
	Capacity = 20;

}

bool URSInventoryComponent::AddItem(ARSBaseItem* Item)
{	// 인벤토리 용량 제한, 아이템인지 확인
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

bool URSInventoryComponent::RemoveItem(ARSBaseItem* Item)
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



