// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "RSMainMenuWidget.generated.h"

UENUM(BlueprintType)
enum class EMenuMode : uint8
{
	MainMenu,
	GameOver,
	GameClear
};


UCLASS()
class RISEOFSUN_API URSMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnStartClicked();

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StartEndText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TitleText;
	UPROPERTY(meta = (BindWidget))
	class UImage* GameStart;
	UPROPERTY(meta = (BindWidget))
	class UImage* GameClear;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu")
	EMenuMode MenuMode = EMenuMode::MainMenu;
};
