// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

void UInventorySlotWidget::SetItemData(FName ItemID, int32 StackCount)
{
    if (StackText)
    {
        StackText->SetText(FText::AsNumber(StackCount));
    }
}