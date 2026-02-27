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
protected:
	virtual void BeginPlay() override;
	
	
};
