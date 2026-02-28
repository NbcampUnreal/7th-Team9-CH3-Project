// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

void UInventorySlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StackText)
    {
        StackText->SetText(FText::GetEmpty());
    }
}

void UInventorySlotWidget::SetItemData(UTexture2D* ItemIconTexture, int32 StackCount)
{
    ItemIcon->SetBrushFromTexture(ItemIconTexture);

    const FText Text = GetStackCountText(StackCount);
    StackText->SetText(Text);
}

FText UInventorySlotWidget::GetStackCountText(int32 StackCount) const
{
    if (StackText)
    {
        if (StackCount > 1)
        {
            return FText::AsNumber(StackCount);
        }
    }

    return FText::GetEmpty();
}
