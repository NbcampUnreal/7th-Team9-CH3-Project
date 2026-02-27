#include "RSExplosiveFlashbangItem.h"
#include "Kismet/GameplayStatics.h"

ARSExplosiveFlashbangItem::ARSExplosiveFlashbangItem()
{
    PrimaryActorTick.bCanEverTick = false;
    Mesh->SetSimulatePhysics(true);
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Mesh->SetCollisionObjectType(ECC_PhysicsBody);
    Mesh->SetCollisionResponseToAllChannels(ECR_Block);
    Mesh->SetLinearDamping(0.2f);
    Mesh->SetAngularDamping(0.1f);
    Mesh->OnComponentHit.AddDynamic(this, &ARSExplosiveFlashbangItem::Hit);
}

void ARSExplosiveFlashbangItem::Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        UGameplayStatics::ApplyRadialDamage(
            this,
            ItemData.AttackPower,
            GetActorLocation(),
            1000.f,
            nullptr,
            TArray<AActor*>(),
            this,
            GetInstigatorController(),
            true
        );

        if (ExplosiveFlashbangEffect)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                ExplosiveFlashbangEffect,
                GetActorLocation()
            );
        }

        if (ExplosiveFlashbangSound)
        {
            UGameplayStatics::PlaySoundAtLocation(
                this,
                ExplosiveFlashbangSound,
                GetActorLocation()
            );
        }


        Destroy();
    }
}
