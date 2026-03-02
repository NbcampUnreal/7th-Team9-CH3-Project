// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickbarWidget.h"
#include "Actor/Character/RSPlayer.h"
#include "InventoryWidget.h"
#include "Actor/Character/Component/RSInventoryComponent.h"
#include <Core/RSGameInstance.h>


void UQuickbarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RSPlayer = Cast<ARSPlayer>(GetOwningPlayer()->GetCharacter());
	if (RSPlayer) {
		QuickbarWidget->InitSlot(2);

        URSGameInstance* RSGameInstance = Cast<URSGameInstance>(GetGameInstance());
        if (!RSGameInstance) return;
        check(RSGameInstance->ItemManager);
        URSItemManager* ItemManager = RSGameInstance->ItemManager;

		const FRSItemData& GrenadeData = ItemManager->GetItemDataByID("Grenade");
		const FRSItemData& FlareData = ItemManager->GetItemDataByID("Flare");

		QuickbarWidget->SetItemByIndex(0, GrenadeData.Thumbnail, RSPlayer->firstThrowableSlot.numThrowables);
		QuickbarWidget->SetItemByIndex(1, FlareData.Thumbnail, RSPlayer->secondThrowableSlot.numThrowables);

		RSPlayer->onGrenadeChanged.AddDynamic(this, &ThisClass::OnGrenadeChanged);
		RSPlayer->onCombatFlareChanged.AddDynamic(this, &ThisClass::OnCombatFlareChanged);
	}
}

void UQuickbarWidget::OnGrenadeChanged(int numThrowables)
{
	QuickbarWidget->SetItemStackCountByIndex(0, numThrowables);
}

void UQuickbarWidget::OnCombatFlareChanged(int numThrowables)
{
	QuickbarWidget->SetItemStackCountByIndex(1, numThrowables);
}
