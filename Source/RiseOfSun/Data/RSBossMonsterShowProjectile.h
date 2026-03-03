#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RSBossMonsterShowProjectile.generated.h"

UCLASS()
class RISEOFSUN_API URSBossMonsterShowProjectile : public UAnimNotify
{
	GENERATED_BODY()
	
	public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
