// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RISEOFSUN_API ARSGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ARSGameMode();//객체가 생성되었을때 한번 호출하는 함수, c++에서 먼저하고 그 다음에 블루프린트에서 한다
	
};
