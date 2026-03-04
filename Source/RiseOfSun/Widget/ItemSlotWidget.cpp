// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemSlotWidget.h"
#include "Actor/Character/RSPlayer.h"
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

void UItemSlotWidget::SetItemData(FName ItemID, UTexture2D* ItemIconTexture, int32 StackCount)
{
	CurrentItemID = ItemID; // 아이템 ID 기억

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

void UItemSlotWidget::UseSlotItem()
{
	// 2. 저장된 ID가 유효할 때만 플레이어의 UseItem을 호출합니다.
	if (!CurrentItemID.IsNone())
	{
		if (ARSPlayer* Player = Cast<ARSPlayer>(GetOwningPlayerPawn()))
		{
			Player->UseItem(CurrentItemID);
		}
	}
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
