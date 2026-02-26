#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "Widget/RSPlayerHUD.h"
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
    
    //인벤토리 컴포넌트 게터
    URSInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
protected:
    UPROPERTY(EditAnywhere)
    class USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere)
    class UCameraComponent* Camera;

    // 인벤토리 컴포넌트 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<class URSInventoryComponent> InventoryComponent;

    // 아이템 줍기/사용 함수
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void PickUpItem(FName ItemID, int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(FName ItemID);

private:


    // ---------- 여기부터 HP 관련 추가 ----------


	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
    void Fire(const FInputActionValue& Value);
    void StopFire(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
    void Shoot();
    void Reloading(const FInputActionValue& Value);
    void LevelUp();
	//카메라 중앙에 조준점 계산함수
    void AimStart();
    void HandleFire();

    //인벤토리
    void HandleToggleInventory();



private:
    //매핑
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

    UPROPERTY(VisibleAnywhere, Category = "Input")
    class UInputAction* ShootingAction;


	// HUD 업데이트 위해 PlayerHUD 참조
    UPROPERTY()
    URSPlayerHUD* PlayerHUD;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* InventoryAction;

public:
    //캐릭터 설정값
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

    //에임 위치
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim")
    FVector LastAimPoint = FVector::ZeroVector;

    FTimerHandle FireTimerHandle;
    UPROPERTY(EditAnywhere)
    float FireInterval = 0.1f; // 발사 간격 (초)

    bool bIsFiring;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim")
    bool bHasAimPoint = false;
    UPROPERTY(EditAnywhere, Category = "CameraTrace")
    float CamRange = 10000.0f;
    UPROPERTY(EditAnywhere, Category = "CameraTrace")
    float FireDebugDuration = 1.0f;
	//카메라 중앙에 조준점 계산할 때 사용할 트레이스 채널
    TEnumAsByte<ECollisionChannel> CamTraceChannel = ECC_Visibility;

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
    TObjectPtr<class URSRifleComponent> RifleComp;

    UUserWidget* GetPlayerHUD() const { return PlayerHUD; }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RifleComp")
	TObjectPtr<class UStaticMeshComponent> RifleMeshComp;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RifleComp")
    TObjectPtr<class USceneComponent> MuzzlePoint;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RifleComp")
    class UNiagaraSystem* MuzzleFlashSystem;
    
	UPROPERTY(EditAnywhere, Category = "Reload")
	class UAnimMontage* ReloadMontage;
};