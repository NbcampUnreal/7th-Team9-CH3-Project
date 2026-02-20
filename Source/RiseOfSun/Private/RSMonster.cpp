#include "RSMonster.h"
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

    // 처음에는 UI 숨김
    HPWidgetComponent->SetVisibility(false);
}

bool ARSMonster::CanAttack(ACharacter* Target)
{
    if (!Target) return false;

    FVector ActorLocation = GetActorLocation();  //몬스터 위치
    FVector PlayerLocation = Target->GetActorLocation();  //플레이어 위치
    const float DistSq = FVector::DistSquared2D(ActorLocation, PlayerLocation);
    
    return DistSq <= AttackRange * AttackRange; // 공격범위
}

FDamageResult ARSMonster::Attack(ARSCharacter* Target)
{
    if (!CanAttack(Target)) return FDamageResult();
    FDamageResult result = ARSCharacter::Attack(Target);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Monster Attack")));
    }
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
            // 만든 몬스터 HP 위젯 클래스로 캐스팅
            URSMonsterWidget* HPWidget = Cast<URSMonsterWidget>(Widget);
            if (HPWidget)
            {
                HPWidget->SetOwnerMonster(this);
            }
        }
    }
}

void ARSMonster::ShowDamageUI()
{
    if (!HPWidgetComponent) return;

    // UI 켜기
    HPWidgetComponent->SetVisibility(true);
    // 기존 타이머가 있으면 취소
    if (GetWorldTimerManager().IsTimerActive(DamageUITimerHandle))
        GetWorldTimerManager().ClearTimer(DamageUITimerHandle);

    // 새로운 타이머 설정
    GetWorldTimerManager().SetTimer(DamageUITimerHandle, [this]()
        {
            if (HPWidgetComponent)
                HPWidgetComponent->SetVisibility(false);
        }, 2.f, false);
}


