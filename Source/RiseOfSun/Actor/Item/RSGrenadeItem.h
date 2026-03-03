#pragma once

#include "CoreMinimal.h"
#include "RSBaseItem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "RSBaseThrowable.h"
#include "RSGrenadeItem.generated.h"

UCLASS()
class RISEOFSUN_API ARSGrenadeItem : public ARSBaseItem
{
	GENERATED_BODY()

public:
	ARSGrenadeItem();

	void ActivateItem(AActor* Activator) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Grenade")
	UNiagaraSystem* ExplosionEffect; // 폭발 이벤트 나이아가라 시스템으로 변경 필요함... ExplosionEffect 수류탄 블루프린트 에디터에 검색

	UPROPERTY(EditAnywhere, Category = "Grenade")
	USoundBase* ExplosionSound;

	EThrowableType type;

	void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

private:

};
