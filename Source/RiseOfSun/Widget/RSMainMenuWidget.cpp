// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/RSMainMenuWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void URSMainMenuWidget::OnStartClicked()
{
	if (MenuMode == EMenuMode::MainMenu)
	{
		UGameplayStatics::OpenLevel(this, "TestLevel");
	}
	else if (MenuMode == EMenuMode::GameOver)
	{
		UGameplayStatics::OpenLevel(this, "TestLevel");
	}
	
	else if (MenuMode == EMenuMode::GameClear)
	{
		UGameplayStatics::OpenLevel(this, "TestLevel");
	}
}
bool URSMainMenuWidget::Initialize()
{
	Super::Initialize();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &URSMainMenuWidget::OnStartClicked);
	}

	return true;
}

void URSMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (MenuMode == EMenuMode::MainMenu)
	{
		GameClear->SetVisibility(ESlateVisibility::Collapsed);
		StartEndText->SetText(FText::FromString("Start"));
		TitleText->SetText(FText::FromString("The Rise Of Sun"));
	}
	else if (MenuMode == EMenuMode::GameOver)
	{
		GameClear->SetVisibility(ESlateVisibility::Collapsed);
		StartEndText->SetText(FText::FromString("Restart"));
		TitleText->SetText(FText::FromString("Game Over"));
	}
	else if (MenuMode == EMenuMode::GameClear)
	{
		GameStart->SetVisibility(ESlateVisibility::Collapsed);
		StartEndText->SetText(FText::FromString("Restart"));
		TitleText->SetText(FText::FromString("Game Clear"));
	}
}
