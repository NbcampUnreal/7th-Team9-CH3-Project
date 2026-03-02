// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UItemSlotWidget;
class UGridPanel;
class UPanelWidget;
class UTexture2D;
/**
 * 
 */
UCLASS()
class RISEOFSUN_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void InitSlot(int32 Count, int32 MaxColumns = 5);

	UFUNCTION(BlueprintCallable)
	void SetItemByIndex(int32 Index, UTexture2D* Texture, int32 StackCount);

	UFUNCTION(BlueprintCallable)
	void SetItemStackCountByIndex(int32 Index, int32 StackCount);
	
	UFUNCTION()
	void SetVisibilityWithBool(bool Visible);

public:
	UPROPERTY(meta = (BindWidget))
	UGridPanel* InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* InventoryPanel;

	// 슬롯 위젯 클래스 (블루프린트에서 지정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> InventorySlotWidgetClass;

private:
	UPROPERTY()
	TArray<TObjectPtr<UItemSlotWidget>> Slots;

};
