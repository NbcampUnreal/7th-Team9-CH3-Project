// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSBaseItem.generated.h"

UCLASS()
class RISEOFSUN_API ARSBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSBaseItem();

	// 월드 정보
	UPROPERTY(Transient)
	class UWorld* World;
	UPROPERTY()
	class URSInventoryComponent* OwningInventory;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
