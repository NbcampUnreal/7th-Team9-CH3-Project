#include "RSGrenadeItem.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Character/RSPlayer.h"

ARSGrenadeItem::ARSGrenadeItem()
{
	PrimaryActorTick.bCanEverTick = false;

	type = EThrowableType::E_FragGrenade;
}

void ARSGrenadeItem::ActivateItem(AActor* Activator)
{

}

void ARSGrenadeItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARSPlayer* Player = Cast<ARSPlayer>(OtherActor);

	if (Player)
	{
		Player->AddThrowable(this->type);

		Destroy();
	}
}