// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "RSPlayer.generated.h"

/**
 * 
 */
UCLASS()
class RISEOFSUN_API ARSPlayer : public ARSCharacter
{
	GENERATED_BODY()
	
	ARSPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

private:
	void InitializationPlayerMesh();

	void InitializationPlayerCamera();
};
