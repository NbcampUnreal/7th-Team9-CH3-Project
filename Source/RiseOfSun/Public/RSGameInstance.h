// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RSGameInstance.generated.h"


UCLASS()
class RISEOFSUN_API URSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	int32 LevelIndex = 0;
	int32 SubLevelIndex = 0;
	int32 MaxLevelIndex = 5;

	virtual void Init() override;
};
