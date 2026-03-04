#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSBossMonsterProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class RISEOFSUN_API ARSBossMonsterProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSBossMonsterProjectile();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
public:
	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 DamageAmount = 250;
};
