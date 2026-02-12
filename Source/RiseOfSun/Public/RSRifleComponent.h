#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RSRifleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RISEOFSUN_API URSRifleComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URSRifleComponent();
	//Ʈ���̽� ä��
	TEnumAsByte<ECollisionChannel> WeaponTraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRange = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireDebugDuration = 1.0f;

	float ReloadDuration = 3.0f;

	int32 AmmoInClip = 30;

	struct FTimerHandle ReloadTimerHandle;

	bool bIsReloading;

	bool bCanFire = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire();

	void Reload();

	void ReloadComplete();
};
