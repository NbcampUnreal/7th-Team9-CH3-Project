#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Actor/Character/RSBossMonster.h"
#include "RSBossMonsterAnimNotify.generated.h"

UCLASS()
class RISEOFSUN_API URSBossMonsterAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	URSBossMonsterAnimNotify();
	[[deprecated]] virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
