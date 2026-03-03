#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RSBossMonsterHideProjectile.generated.h"

UCLASS()
class RISEOFSUN_API URSBossMonsterHideProjectile : public UAnimNotify
{
	GENERATED_BODY()
	
	public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
