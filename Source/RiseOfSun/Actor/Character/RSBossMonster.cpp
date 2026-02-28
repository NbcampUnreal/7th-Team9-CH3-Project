#include "Actor/Character/RSBossMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widget/RSMonsterWidget.h"

ARSBossMonster::ARSBossMonster()
{
}

void ARSBossMonster::BeginPlay()
{
	Super::BeginPlay();

	//몬스터의 기본 속력
	GetCharacterMovement()->MaxWalkSpeed = NormalMovementSpeed;

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

int32 ARSBossMonster::HitDamage(int32 DamageAmount)
{
	if (bIsDead)
	{
		return 0;
	}
	int32 Damage = Super::HitDamage(DamageAmount);
	
	return Damage;
}
