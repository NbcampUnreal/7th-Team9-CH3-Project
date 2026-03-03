#include "RSBossMonsterShowProjectile.h"
#include "Actor/Character/RSBossMonster.h"

void URSBossMonsterShowProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	ARSBossMonster* Boss =
		Cast<ARSBossMonster>(MeshComp->GetOwner());

	if (Boss)
	{
		Boss->ShowRock();
	}
}
