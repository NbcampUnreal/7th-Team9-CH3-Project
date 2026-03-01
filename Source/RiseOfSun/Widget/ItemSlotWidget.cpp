// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemSlotWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

const int32 UItemSlotWidget::EmptyCount = 0;

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StackText)
	{
		StackText->SetText(FText::GetEmpty());
	}
}

void UItemSlotWidget::SetItemData(UTexture2D* ItemIconTexture, int32 StackCount)
{
	if (!ItemIcon) return;
	
	if (ItemIconTexture)
	{
		ItemIcon->SetBrushFromTexture(ItemIconTexture);
		SetStackText(StackCount);
	}
	else
	{
		ItemIcon->SetBrush(FSlateBrush());
		SetStackText(EmptyCount);
	}
}

void UItemSlotWidget::SetStackText(int32 StackCount)
{
	const FText Text = GetStackCountText(StackCount);
	StackText->SetText(Text);
}

FText UItemSlotWidget::GetStackCountText(int32 StackCount) const
{
	if (StackText)
	{
		if (StackCount >= 1)
		{
			return FText::AsNumber(StackCount);
		}
	}

	return FText::GetEmpty();
}
