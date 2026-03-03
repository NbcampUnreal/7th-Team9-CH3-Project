#include "RSBossMonsterAnimNotify.h"

URSBossMonsterAnimNotify::URSBossMonsterAnimNotify()
{
	
}

void URSBossMonsterAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	ARSBossMonster* Boss = Cast<ARSBossMonster>(MeshComp->GetOwner());
	if (!Boss) return;

	Boss->FireProjectile();
}