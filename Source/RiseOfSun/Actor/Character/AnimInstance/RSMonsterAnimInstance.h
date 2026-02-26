// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RSMonsterAnimInstance.generated.h"


UCLASS()
class RISEOFSUN_API URSMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	URSMonsterAnimInstance();
	virtual void NativeInitializeAnimation() override; // 애니메이션이 생성되면 호출되는 함수.

	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 프레임마다 호출되는 함수.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class ACharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UCharacterMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float MoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool isFalling = false;
	
protected:

};
