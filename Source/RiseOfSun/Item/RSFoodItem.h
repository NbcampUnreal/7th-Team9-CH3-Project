#pragma once

#include "CoreMinimal.h"
#include "Item/RSItemBase.h"
#include "RSFoodItem.generated.h"

UCLASS()
class RISEOFSUN_API URSFoodItem : public URSItemBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float HealthToHeal;

protected:

	virtual void Use(class ARSPlayer* Player) override;
};