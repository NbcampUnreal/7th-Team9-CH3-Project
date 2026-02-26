// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/RSMainMenuWidget.h"

#include "Kismet/GameplayStatics.h"

void URSMainMenuWidget::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("TestLevel"));
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