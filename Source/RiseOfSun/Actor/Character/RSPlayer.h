#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "Widget/RSPlayerHUD.h"
#include "InputActionValue.h"
#include "Actor/Item/RSBaseThrowable.h"
#include "RSPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEXPChanged); // EXP 변경 이벤트 델리게이트

// Declare the delegate for the number of throwables in slot 1.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGrenadeChanged, int, numThrowables);

// Declare the delegate for the number of throwables in slot 2.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatFlareChanged, int, numThrowables);

USTRUCT(BlueprintType)
struct FThrowableSlot
{
    GENERATED_BODY()

    // The type of throwable in the slot.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable slot")
    EThrowableType throwableType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable slot")
    TSubclassOf<ARSBaseThrowable> throwableClass;

    // The number of throwables in the slot.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable slot")
    int numThrowables;
};

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

    void AddThrowable(EThrowableType ItemType);

    void RecoverHealth(float Amount);

    // 아이템 줍기/사용 함수
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void PickUpItem(FName ItemID, int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UseItem(FName ItemID);

protected:
    UPROPERTY(EditAnywhere)
    class USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere)
    class UCameraComponent* Camera;

    // 인벤토리 컴포넌트 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<class URSInventoryComponent> InventoryComponent;

    // 1~0번까지 10개의 슬롯 액션 (에디터에서 할당)
    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* QuickSlotActions[10];

    void QuickSlot(int32 Index);
    void QuickSlotInput(int32 SlotIndex);

    // 각 키에 바인딩할 함수들
    UFUNCTION()
    void OnQuickSlot1(const FInputActionValue& Value) { QuickSlotInput(0); }
    UFUNCTION()
    void OnQuickSlot2(const FInputActionValue& Value) { QuickSlotInput(1); }
    UFUNCTION()
    void OnQuickSlot3(const FInputActionValue& Value) { QuickSlotInput(2); }
    UFUNCTION()
    void OnQuickSlot4(const FInputActionValue& Value) { QuickSlotInput(3); }
    UFUNCTION()
    void OnQuickSlot5(const FInputActionValue& Value) { QuickSlotInput(4); }
    UFUNCTION()
    void OnQuickSlot6(const FInputActionValue& Value) { QuickSlotInput(5); }
    UFUNCTION()
    void OnQuickSlot7(const FInputActionValue& Value) { QuickSlotInput(6); }
    UFUNCTION()
    void OnQuickSlot8(const FInputActionValue& Value) { QuickSlotInput(7); }
    UFUNCTION()
    void OnQuickSlot9(const FInputActionValue& Value) { QuickSlotInput(8); }
    UFUNCTION()
    void OnQuickSlot0(const FInputActionValue& Value) { QuickSlotInput(9); }

private:


    // ---------- 여기부터 HP 관련 추가 ----------


	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
    void Fire(const FInputActionValue& Value);
    void StopFire(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
    void Shoot();
	void StopShoot();
    void Reloading(const FInputActionValue& Value);
    void LevelUp();
	//카메라 중앙에 조준점 계산함수
    void AimStart();
    void HandleFire();
	

    //인벤토리
    void HandleToggleInventory();
    
   	void PlayFireSound();
    void ResetFireSound();
    virtual void Die() override;
	UFUNCTION()
	void HandleReloadStarted();
    // Use a throwable based on the type
    void UseThrowable(TSubclassOf<ARSBaseThrowable> ThrowableClass);
    // Use the throwable in Throwable Slot 1
    void UseGrenade(const FInputActionValue& Value);
    // Use the throwable in Throwable Slot 2
    void UseCombatFlare(const FInputActionValue& Value);

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

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* GrenadeAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* CombatFlareAction;

    UPROPERTY()
    class URSGameInstance* GameInstanceRef;

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
	bool bCanPlayFireSound = true;
	bool bIsShoot = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim")
    bool bHasAimPoint = false;
    UPROPERTY(EditAnywhere, Category = "CameraTrace")
    float CamRange = 10000.0f;
    UPROPERTY(EditAnywhere, Category = "CameraTrace")
    float FireDebugDuration = 1.0f;
	
	FTimerHandle FireSoundTimerHandle;
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
	
	UPROPERTY(EditAnywhere, Category = "Die")
	class UAnimMontage* DieMontage;

    // The first throwable slot for the player.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable Slot")
    FThrowableSlot firstThrowableSlot;

    // The second throwable slot for the player.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable Slot")
    FThrowableSlot secondThrowableSlot;

    // The delegate for the number of throwables in slot 1.
    UPROPERTY(BlueprintAssignable, Category = "Throwable Slot")
    FOnGrenadeChanged onGrenadeChanged;

    // The delegate for the number of throwables in slot 2.
    UPROPERTY(BlueprintAssignable, Category = "Throwable Slot")
    FOnCombatFlareChanged onCombatFlareChanged; 
};
