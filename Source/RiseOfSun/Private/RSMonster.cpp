#include "RSMonster.h"
#include "RSPlayer.h"
#include "RSMonsterWidget.h"

ARSMonster::ARSMonster()
{
    AttackRange = 200.0f;

    // HP Widget 생성
    HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
    HPWidgetComponent->SetupAttachment(RootComponent);

    // 머리 위 위치
    HPWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 250.f));

    // 월드 공간
    HPWidgetComponent->SetWidgetSpace(EWidgetSpace::World);

    // 크기
    HPWidgetComponent->SetDrawSize(FVector2D(300.f, 80.f));
}

bool ARSMonster::CanAttack(ACharacter* Target)
{
    FVector ActorLocation = GetActorLocation();  //몬스터 위치
    FVector PlayerLocation = Target->GetActorLocation();  //플레이어 위치
    const float DistSq = FVector::DistSquared2D(ActorLocation, PlayerLocation);
    
    return DistSq <= AttackRange * AttackRange; // 공격범위
}

FDamageResult ARSMonster::Attack(ARSCharacter* Target)
{
    if (!CanAttack(Target)) return FDamageResult();
    FDamageResult result = ARSCharacter::Attack(Target);
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

    if (AnimInstance)
    {
        if (AttackMontage)
        {
            AnimInstance->Montage_Play(AttackMontage);
        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Monster Attack")));
    return result;
}

void ARSMonster::BeginPlay()
{
    Super::BeginPlay();

    if (HPWidgetComponent)
    {
        UUserWidget* Widget = HPWidgetComponent->GetUserWidgetObject();
        if (Widget)
        {
            // 네가 만든 몬스터 HP 위젯 클래스로 캐스팅
            URSMonsterWidget* HPWidget = Cast<URSMonsterWidget>(Widget);
            if (HPWidget)
            {
                HPWidget->SetOwnerMonster(this);
            }
        }
    }
}


