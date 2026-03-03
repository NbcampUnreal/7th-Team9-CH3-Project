#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/RSMonster.h"
#include "Slate/SGameLayerManager.h"
#include "Actor/Character/RSPlayer.h"
#include "RSBossMonster.generated.h"

UCLASS()
class RISEOFSUN_API ARSBossMonster : public ARSMonster
{
	GENERATED_BODY()
	
public:
	ARSBossMonster();
	
	UFUNCTION(BlueprintCallable)
	void ShowRock();
	void HideRock();

	virtual void BeginPlay() override;
	virtual int32 HitDamage(int32 DamageAmount)override;
	virtual void Die()override;

	void FireProjectile();
	void RangedAttack();
	
	UFUNCTION(BlueprintCallable)
	void OnRangedAttackEnd();
	
	FTimerHandle AttackTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "RangeAttack")
	float AttackInterval;
	
	UPROPERTY(EditAnywhere, Category = "RangeAttack")
	UAnimMontage* RangedAttackMontage;

	
	UPROPERTY(EditAnywhere, Category = "RangedAttack")
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RockMesh;
};
