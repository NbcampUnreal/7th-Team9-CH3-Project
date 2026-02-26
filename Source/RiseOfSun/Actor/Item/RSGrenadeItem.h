#pragma once

#include "CoreMinimal.h"
#include "RSBaseItem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "RSGrenadeItem.generated.h"


UCLASS()
class RISEOFSUN_API ARSGrenadeItem : public ARSBaseItem
{
	GENERATED_BODY()

public:
	ARSGrenadeItem();

protected:
<<<<<<< Updated upstream
=======
	UPROPERTY(EditAnywhere, Category = "Grenade")
	UNiagaraSystem* ExplosionEffect; // 폭발 이벤트 나이아가라 시스템으로 변경 필요함... ExplosionEffect 수류탄 블루프린트 에디터에 검색

	UPROPERTY(EditAnywhere, Category = "Grenade")
	USoundBase* ExplosionSound;

>>>>>>> Stashed changes
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
	
};
