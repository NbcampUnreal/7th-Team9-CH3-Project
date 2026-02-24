#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSMonsterWidget.generated.h"  

UCLASS()
class RISEOFSUN_API URSMonsterWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetOwnerMonster(class ARSMonster* NewOwner);

    UFUNCTION(BlueprintCallable)
    float GetHPPercent() const;

private:
    UPROPERTY()
    ARSMonster* OwnerMonster = nullptr;
};
