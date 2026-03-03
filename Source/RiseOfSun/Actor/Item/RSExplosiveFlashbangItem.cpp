#include "RSExplosiveFlashbangItem.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Character/RSPlayer.h"

ARSExplosiveFlashbangItem::ARSExplosiveFlashbangItem()
{
	PrimaryActorTick.bCanEverTick = false;

	type = EThrowableType::E_CombatFlare;
}

void ARSExplosiveFlashbangItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARSPlayer* Player = Cast<ARSPlayer>(OtherActor);

	if (Player)
	{
		Player->AddThrowable(this->type);

		Destroy();
	}
}
