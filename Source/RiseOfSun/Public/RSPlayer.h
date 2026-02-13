#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "InputActionValue.h"
#include "RSPlayer.generated.h"

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
	
	virtual FDamageResult Attack(ARSCharacter* Target) override;
protected:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

private:
	void InitializationPlayerMesh();
	void InitializationPlayerCamera();
	void InitializationInput();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


private:
	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputMappingContext* DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* LookAction;

public:
	UPROPERTY(EditAnywhere)
	float mouseSpeed = 30.0f;
};
