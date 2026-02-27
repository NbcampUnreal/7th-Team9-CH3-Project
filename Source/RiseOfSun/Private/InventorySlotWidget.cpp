// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

void UInventorySlotWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UInventorySlotWidget::SetItemData(FName ItemID, int32 StackCount)
{
    if (StackText)
    {
        if (StackCount > 1)
        {
            StackText->SetText(FText::AsNumber(StackCount));
        }
        else
        {
            StackText->SetText(FText::GetEmpty()); // 1개면 숨김
        }
    }
}