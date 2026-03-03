#pragma once

#include "CoreMinimal.h"
#include "RSBaseItem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "RSExplosiveFlashbangItem.generated.h"

UCLASS()
class RISEOFSUN_API ARSExplosiveFlashbangItem : public ARSBaseItem
{
	GENERATED_BODY()

public:
	ARSExplosiveFlashbangItem();

protected:
	UPROPERTY(EditAnywhere, Category = "FlashGrenade")
	UNiagaraSystem* ExplosiveFlashbangEffect;

	UPROPERTY(EditAnywhere, Category = "FlashGrenade")
	USoundBase* ExplosiveFlashbangSound;

	
};
