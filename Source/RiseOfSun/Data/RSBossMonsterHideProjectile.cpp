#include "RSBossMonsterHideProjectile.h"
#include "Actor/Character/RSBossMonster.h"

void URSBossMonsterHideProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	ARSBossMonster* Boss =
		Cast<ARSBossMonster>(MeshComp->GetOwner());

	if (Boss)
	{
		Boss->HideRock();
	}
}
