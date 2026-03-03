#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "RSBaseItem.h"
#include "RSBaseThrowable.generated.h"

UENUM(BlueprintType)
enum class EThrowableType : uint8
{
	E_FragGrenade		UMETA(DisplayName = "FragGrenade"),
	E_CombatFlare		UMETA(DisplayName = "CombatFlare")
};

UCLASS()
class RISEOFSUN_API ARSBaseThrowable : public AActor
{
	GENERATED_BODY()
	
public:
	ARSBaseThrowable();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Throwable")
	UNiagaraSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, Category = "Throwable")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* CollisionComponent;

	// The StaticMesh Component for the throwable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	// The type of the throwable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable")
	EThrowableType type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable")
	float Damage;

	

public:
	// The ProjectileMovement Component for the throwable. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* projectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable")
	float ThrowSpeed = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable")
	float ExplosionRadius = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable")
	float ExplosionDelay = 2.0f;

	FTimerHandle ExplosionTimer;

	UFUNCTION()
	void Explode();
};