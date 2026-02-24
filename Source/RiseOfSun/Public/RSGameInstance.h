// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RSItemManager.h"
#include "RSGameInstance.generated.h"


UCLASS()
class RISEOFSUN_API URSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY()
	//현재 플레이어가 있는 레벨
	int32 LevelIndex = 0;

	UPROPERTY()
	//하위 레벨이나 챕터, 작은 구역 번호
	int32 SubLevelIndex = 0;

	UPROPERTY()
	//총 레벨 개수 또는 마지막 레벨 번호
	int32 MaxLevelIndex = 5;

	virtual void Init() override;

	UPROPERTY()
	TObjectPtr<URSItemManager> ItemManager;
};
