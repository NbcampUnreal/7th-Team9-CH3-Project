// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidget.h"
#include "ItemSlotWidget.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/PanelWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::InitSlot(int32 Count, int32 MaxColumns)
{
	InventoryGrid->ClearChildren();
	Slots.SetNum(Count);

	for (int32 i = 0; i < Count; i++)
	{
		if (InventorySlotWidgetClass)
		{
			UItemSlotWidget* SlotWidget =
				CreateWidget<UItemSlotWidget>(GetWorld(), InventorySlotWidgetClass);
			
			if (SlotWidget)
			{
				Slots[i] = SlotWidget;
				// 🔹 Grid 위치 계산
				int32 Row = i / MaxColumns;
				int32 Column = i % MaxColumns;
				UE_LOG(LogTemp, Warning, TEXT("Inventory Slot Create!!!! %d, %d"), Row, Column);

				UGridSlot* GridSlot = InventoryGrid->AddChildToGrid(SlotWidget);
				GridSlot->SetRow(Row);
				GridSlot->SetColumn(Column);
				GridSlot->SetHorizontalAlignment(HAlign_Fill);
				GridSlot->SetVerticalAlignment(VAlign_Fill);
			}
		}
	}
}

void UInventoryWidget::SetItemByIndex(int32 Index, UTexture2D* Texture, int32 StackCount)
{
	if (Slots[Index])
	{
		Slots[Index]->SetItemData(Texture, StackCount);
	}
}

void UInventoryWidget::SetItemStackCountByIndex(int32 Index, int32 StackCount)
{
	if (Slots[Index])
	{
		Slots[Index]->SetStackText(StackCount);
	}
}

void UInventoryWidget::SetVisibilityWithBool(bool Visible)
{
	InventoryPanel->SetVisibility(
		Visible ? ESlateVisibility::Visible
		: ESlateVisibility::Hidden
	);
}
