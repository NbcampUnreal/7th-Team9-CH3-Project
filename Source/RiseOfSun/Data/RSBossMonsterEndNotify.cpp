#include "RSBossMonsterEndNotify.h"
#include "Actor/Character/RSBossMonster.h"

void URSBossMonsterEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)
	{
		return;
	}
	
	ARSBossMonster* Boss = Cast<ARSBossMonster>(MeshComp->GetOwner());
	if (Boss)
	{
		Boss->OnRangedAttackEnd();
	}
}
