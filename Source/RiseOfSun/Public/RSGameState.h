// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RSGameState.generated.h"

/**
 * 
 */
UCLASS()
class RISEOFSUN_API ARSGameState : public AGameState
{
	GENERATED_BODY()
	

public:
	ARSGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	int32 Kills = 0;

};
