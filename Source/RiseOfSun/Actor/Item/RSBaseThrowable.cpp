#include "RSBaseThrowable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Actor/Character/RSCharacter.h"

ARSBaseThrowable::ARSBaseThrowable()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCompnent"));
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = CollisionComponent;

	// Set up Components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	projectileMovement->UpdatedComponent = CollisionComponent;
	projectileMovement->InitialSpeed = 0.f;
	projectileMovement->MaxSpeed = 3000.f;
	projectileMovement->bShouldBounce = true;
	projectileMovement->Bounciness = 0.3f;
	projectileMovement->ProjectileGravityScale = 1.0f;

	// Set default values for variables.
	type = EThrowableType::E_FragGrenade;
	Damage = 0.f;
}

// Called when the game starts or when spawned
void ARSBaseThrowable::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimer,
		this,
		&ARSBaseThrowable::Explode,
		ExplosionDelay,
		false
	);
}

void ARSBaseThrowable::Explode()
{
	APawn* InstigatorPawn = GetInstigator();
	AController* InstigatorController =
		InstigatorPawn ? InstigatorPawn->GetController() : nullptr;

	UGameplayStatics::ApplyRadialDamage(
		this,
		Damage,
		GetActorLocation(),
		ExplosionRadius,
		nullptr,
		TArray<AActor*>(),
		this,
		InstigatorController,
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




