
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RSCharacter.generated.h"

UCLASS()
class RISEOFSUN_API ARSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARSCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
