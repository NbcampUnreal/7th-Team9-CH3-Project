// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickbarWidget.generated.h"

class UInventoryWidget;
class ARSPlayer;
/**
 * 
 */
UCLASS()
class RISEOFSUN_API UQuickbarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

    UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "Quickbar")
    UInventoryWidget* QuickbarWidget;
private:
	UFUNCTION()
	void OnGrenadeChanged(int numThrowables);
	UFUNCTION()
	void OnCombatFlareChanged(int numThrowables);
private:
	UPROPERTY()
	TObjectPtr<ARSPlayer> RSPlayer;
};
