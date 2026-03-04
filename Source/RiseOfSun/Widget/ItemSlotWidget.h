// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RISEOFSUN_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetItemData(FName InItemID, UTexture2D* ItemIconTexture, int32 StackCount);

	UFUNCTION(BlueprintCallable)
	void SetStackText(int32 StackCount);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StackText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void UseSlotItem();

protected:
	// 현재 슬롯이 어떤 아이템인지 저장 (사용할 때 필요)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FName CurrentItemID;

private:
	FText GetStackCountText(int32 StackCount) const;

	static const int32 EmptyCount;
};
