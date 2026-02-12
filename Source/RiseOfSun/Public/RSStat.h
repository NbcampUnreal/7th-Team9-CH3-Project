// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RSStat.generated.h"


USTRUCT(BlueprintType)
struct RISEOFSUN_API FRSStat
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float CurrentHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackDamage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Defense = 5.0f;

	
};
