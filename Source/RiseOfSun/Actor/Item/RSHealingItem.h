#pragma once

#include "CoreMinimal.h"
#include "RSBaseItem.h"
#include "RSHealingItem.generated.h"


UCLASS()
class RISEOFSUN_API ARSHealingItem : public ARSBaseItem
{
	GENERATED_BODY()
	
public:
	ARSHealingItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
