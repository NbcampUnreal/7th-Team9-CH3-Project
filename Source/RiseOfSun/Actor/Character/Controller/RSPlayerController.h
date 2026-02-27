// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RISEOFSUN_API ARSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> StartMenuClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> StartMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>HUDWidget;

	//UFUNCTION(BlueprintCallable, Category = "HUD")
	//UUserWidget* HUDWidget() const;
protected:
	virtual void BeginPlay() override;
	
	
};
