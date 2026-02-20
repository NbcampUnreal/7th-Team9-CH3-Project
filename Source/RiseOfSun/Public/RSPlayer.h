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
    void AddEXP(float ExpAmount);

    UPROPERTY(BlueprintAssignable)
    FOnEXPChanged OnEXPChanged;
protected:
    UPROPERTY(EditAnywhere)
    class USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere)
    class UCameraComponent* Camera;

private:


    // ---------- 여기부터 HP 관련 추가 ----------


	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
    void Reloading(const FInputActionValue& Value);
    void LevelUp();


private:
	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputMappingContext* DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* LookAction;

    UPROPERTY(VisibleAnywhere, Category = "Input")
    class UInputAction* FireAction;

    UPROPERTY(VisibleAnywhere, Category = "Input")
    class UInputAction* AimAction;

    UPROPERTY(VisibleAnywhere, Category = "Input")
    class UInputAction* ReloadingAction;


	// HUD 업데이트 위해 PlayerHUD 참조
    UPROPERTY()
    UUserWidget* PlayerHUD;

public:
	UPROPERTY(EditAnywhere)
	float mouseSpeed = 30.0f;

	UPROPERTY(EditAnywhere)
	float playerMoveSpeed = 350.0f;//캐릭터 속도 설정 값

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
    float CurrentEXP;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
    int32 MaxEXP;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
    int32 Level;
    
    // Getter: 현재 EXP
    UFUNCTION(BlueprintPure, Category = "Player Stats")
    float GetCurrentEXP() const { return CurrentEXP; }

    // Getter: 최대 EXP
    UFUNCTION(BlueprintPure, Category = "Player Stats")
    int32 GetMaxEXP() const { return MaxEXP; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetclass;

	// 라이플 컴포넌트 클래스 참조 (BP에서 설정 가능)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RifleComp")
    TObjectPtr<class URSRifleSceneComponent> RifleComp;


    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RifleComp")
	TObjectPtr<class UStaticMeshComponent> RifleMeshComp;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RifleComp")
    TObjectPtr<class USceneComponent> MuzzlePoint;

};
