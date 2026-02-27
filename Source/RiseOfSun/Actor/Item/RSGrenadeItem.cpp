#include "RSGrenadeItem.h"
#include "Kismet/GameplayStatics.h"

ARSGrenadeItem::ARSGrenadeItem()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_PhysicsBody);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetLinearDamping(0.2f);
	Mesh->SetAngularDamping(0.1f);
	Mesh->OnComponentHit.AddDynamic(this, &ARSGrenadeItem::OnHit);
}

void ARSGrenadeItem::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 자기 자신 제외
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grenade Hit!"));

		// 반경 데미지 (예시)
		UGameplayStatics::ApplyRadialDamage(
			this,
			ItemData.AttackPower,                        // 데미지
			GetActorLocation(),            // 위치
			300.f,                         // 반경
			nullptr, // 어떤 종류의 데미지인지 지정하는 자리
			TArray<AActor*>(), //빈 배열 데미지를 받지 않을 액터 목록
			this, //ARSGrenadeItem 자기 자신
			GetInstigatorController(), //주체(소유자)
			true
		);

		if (ExplosionEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(

				GetWorld(),
				ExplosionEffect,
				GetActorLocation()
			);
		}
		if (ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				ExplosionSound,
				GetActorLocation()
			);
		}

		Destroy();
	}
}
