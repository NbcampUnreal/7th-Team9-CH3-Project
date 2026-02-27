// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RISEOFSUN_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();

	UFUNCTION(BlueprintCallable)
	void SetItemData(FName ItemID, int32 StackCount);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StackText;
};
