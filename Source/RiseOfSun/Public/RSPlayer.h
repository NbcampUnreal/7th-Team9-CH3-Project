#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "RSPlayer.generated.h"

UCLASS()
class RISEOFSUN_API ARSPlayer : public ARSCharacter
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    ARSPlayer();
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

    // ---------- 여기부터 HP 관련 추가 ----------

    // 최대 HP (BP에서 읽기만 가능, 코드에서 수정 금지)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
    float MaxHp = 100.0f;

    // 현재 HP
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
    float CurrentHp = 100.0f;

public:
    // Getter: 현재 HP
    UFUNCTION(BlueprintCallable, Category = "Player Stats")
    float GetCurrentHp() const { return CurrentHp; }

    // Getter: 최대 HP
    UFUNCTION(BlueprintPure, Category = "Player Stats")
    float GetMaxHp() const { return MaxHp; }

    // Setter: 현재 HP
    UFUNCTION(BlueprintCallable, Category = "Player Stats")
    void SetCurrentHp(float NewHp)
    {
        CurrentHp = FMath::Clamp(NewHp, 0.0f, MaxHp);
    }
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetclass;
};
