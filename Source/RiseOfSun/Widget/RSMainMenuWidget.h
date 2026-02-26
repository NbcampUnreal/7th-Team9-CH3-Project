// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "RSMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class RISEOFSUN_API URSMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnStartClicked();

	virtual bool Initialize() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;
	
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* MainMenuWidget;
};
