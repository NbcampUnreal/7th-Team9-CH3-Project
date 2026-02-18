#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "InputActionValue.h"
#include "RSPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEXPChanged); // EXP 변경 이벤트 델리게이트

UCLASS()
class RISEOFSUN_API ARSPlayer : public ARSCharacter
{
    GENERATED_BODY()

public:
    ARSPlayer();

	virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual FDamageResult Attack(ARSCharacter* Target) override;

    // ---------- 여기부터 EXP 관련 추가 ----------
    UFUNCTION(BlueprintCallable)
    void AddEXP(int32 ExpAmount);

    UPROPERTY(BlueprintAssignable)
    FOnEXPChanged OnEXPChanged;
protected:
    UPROPERTY(EditAnywhere)
    class USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere)
    class UCameraComponent* Camera;

private:
    void InitializationPlayerMesh();

    void InitializationPlayerCamera();

    // ---------- 여기부터 HP 관련 추가 ----------

	void InitializationInput();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
    void LevelUp();


private:
	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputMappingContext* DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* LookAction;

	// HUD 업데이트 위해 PlayerHUD 참조
    UPROPERTY()
    UUserWidget* PlayerHUD;

public:
	UPROPERTY(EditAnywhere)
	float mouseSpeed = 30.0f;

	UPROPERTY(EditAnywhere)
	float playerMoveSpeed = 350.0f;//캐릭터 속도 설정 값
    // 최대 HP (BP에서 읽기만 가능, 코드에서 수정 금지)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
    float MaxHp;

    // 현재 HP
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
    float CurrentHp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
    int32 CurrentEXP;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
    int32 MaxEXP;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
    int32 Level;
    
    // Getter: 현재 HP
    UFUNCTION(BlueprintPure, Category = "Player Stats")
    float GetCurrentHp() const { return CurrentHp; }

    // Getter: 최대 HP
    UFUNCTION(BlueprintPure, Category = "Player Stats")
    float GetMaxHp() const { return MaxHp; }

	// Getter: 현재 EXP
    UFUNCTION(BlueprintPure, Category = "Player Stats")
    int32 GetCurrentEXP() const { return CurrentEXP; }

    // Getter: 최대 EXP
    UFUNCTION(BlueprintPure, Category = "Player Stats")
    int32 GetMaxEXP() const { return MaxEXP; }

    // Setter: 현재 HP
    UFUNCTION(BlueprintCallable, Category = "Player Stats")
    void SetCurrentHp(float NewHp)
    {
        CurrentHp = FMath::Clamp(NewHp, 0.0f, MaxHp);
    }
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetclass;
};
