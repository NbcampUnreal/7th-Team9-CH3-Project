#include "RSBossMonsterProjectile.h"
#include "Components/SphereComponent.h"
#include "Actor/Character/RSPlayer.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Character/RSCharacter.h"


ARSBossMonsterProjectile::ARSBossMonsterProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    RootComponent = CollisionComp;
    CollisionComp->InitSphereRadius(30.f);
    
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 
    CollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CollisionComp->SetGenerateOverlapEvents(true);
    
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(RootComponent);
    StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
    StaticMesh->SetSimulatePhysics(false);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 1.0f;
}

void ARSBossMonsterProjectile::BeginPlay()
{
    Super::BeginPlay();
    
    if (CollisionComp)
    {
        CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ARSBossMonsterProjectile::OnOverlap);
    }
}

void ARSBossMonsterProjectile::OnOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("투사체 오버랩 발생! 상대방 액터: %s"), *OtherActor->GetName());
        
        if (ARSPlayer* HitPlayer = Cast<ARSPlayer>(OtherActor))
        {
            HitPlayer->HitDamage(DamageAmount);
            Destroy();
        }
    }
}
